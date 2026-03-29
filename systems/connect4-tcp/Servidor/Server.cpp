#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

#define ROW 6
#define COL 7

std::mutex mtx; 
std::ofstream log_file("Servidor_log.txt");

void log_info(const std::string& msg) {
    mtx.lock();
    std::cout << "[INFO] " << msg << std::endl;
    log_file << "[INFO] " << msg << std::endl;
    mtx.unlock();
}

void log_error(const std::string& msg) {
    mtx.lock();
    std::cerr << "[ERROR] " << msg << std::endl;
    log_file << "[ERROR] " << msg << std::endl;
    mtx.unlock();
}

class Servidor {
public:
    Servidor(int puerto);
    void run();

private:
    int server_fd;
    struct sockaddr_in address;
    int addrlen;
    std::vector<std::thread> client_threads;

    void client(int cliente_socket, const char* cliente_ip, int cliente_port);
    void tablero_init(char tablero[ROW][COL]);
    bool check_winner(char tablero[ROW][COL], char jugador);
    bool check_horizontal(char tablero[ROW][COL], char jugador);
    bool check_vertical(char tablero[ROW][COL], char jugador);
    bool check_diagonal(char tablero[ROW][COL], char jugador);
    bool tablero_lleno(char tablero[ROW][COL]);
    void imprimir_tablero(char tablero[ROW][COL]);
};

Servidor::Servidor(int puerto) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        log_error("Fallo en Socket!");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(puerto);
    addrlen = sizeof(address);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        log_error("Fallo en Bind!");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        log_error("Fallo en Listen!");
        exit(EXIT_FAILURE);
    }
}

void Servidor::run() {
    std::cout << "Esperando conexiones..." << std::endl;
    while (true) {
        struct sockaddr_in cliente_address;
        socklen_t cliente_addrlen = sizeof(cliente_address);
        int cliente_socket = accept(server_fd, (struct sockaddr *)&cliente_address, &cliente_addrlen);
        if (cliente_socket < 0) {
            log_error("Fallo en Accept!");
            continue;
        }
        char cliente_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &cliente_address.sin_addr, cliente_ip, INET_ADDRSTRLEN);
        int cliente_port = ntohs(cliente_address.sin_port);
        std::cout << "Juego nuevo [" << cliente_ip << ":" << cliente_port << "]" << std::endl;
        client_threads.emplace_back(&Servidor::client, this, cliente_socket, cliente_ip, cliente_port);
    }

    // antes de apagar el servidor, se cerrarán todos los threads
    for (auto& thread : client_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Servidor::client(int cliente_socket, const char* cliente_ip, int cliente_port) {
    char tablero[ROW][COL];
    tablero_init(tablero);

    char buffer[1024] = {0};
    int read_size;
    char jugador = 'S';
    std::string tablero_str;
    for (int f = 0; f < ROW; ++f) {
        for (int c = 0; c < COL; ++c) {
            tablero_str += tablero[f][c];
            tablero_str += ' ';
        }
        tablero_str += '\n';
    }
    send(cliente_socket, tablero_str.c_str(), tablero_str.size(), 0);

    while ((read_size = read(cliente_socket, buffer, 1024)) > 0) {
        mtx.lock();
        std::cout << "[" << cliente_ip << ":" << cliente_port << "] cliente juega columna " << buffer << std::endl;
        // Se espera que el cliente envíe un solo caracter, en caso contrario, se tomará el primer caracter
        int col = buffer[0] - '0'; 
        for (int i = ROW - 1; i >= 0; --i) {
            if (tablero[i][col] == '-') {
                tablero[i][col] = 'C';
                break;
            }
        }

        if (check_winner(tablero, 'C')) {
            std::string tablero_str;
            for (int f = 0; f < ROW; ++f) {
                for (int c = 0; c < COL; ++c) {
                    tablero_str += tablero[f][c];
                    tablero_str += ' ';
                }
                tablero_str += '\n';
            }
            send(cliente_socket, tablero_str.c_str(), tablero_str.size(), 0);
            send(cliente_socket, "Gana el CLiente\n", strlen("Gana el Cliente\n"), 0);
            mtx.unlock();
            break;
        } else if (tablero_lleno(tablero)) {
            std::string tablero_str;
            for (int f = 0; f < ROW; ++f) {
                for (int c = 0; c < COL; ++c) {
                    tablero_str += tablero[f][c];
                    tablero_str += ' ';
                }
                tablero_str += '\n';
            }
            send(cliente_socket, tablero_str.c_str(), tablero_str.size(), 0);
            send(cliente_socket, "Empate\n", strlen("Empate\n"), 0);
            mtx.unlock();
            break;
        }

        int server_col = rand() % COL;
        for (int i = ROW - 1; i >= 0; --i) {
            if (tablero[i][server_col] == '-') {
                tablero[i][server_col] = 'S';
                break;
            }
        }

        std::string tablero_str;
        for (int f = 0; f < ROW; ++f) {
            for (int c = 0; c < COL; ++c) {
                tablero_str += tablero[f][c];
                tablero_str += ' ';
            }
            tablero_str += '\n';
        }
        send(cliente_socket, tablero_str.c_str(), tablero_str.size(), 0);
        if (check_winner(tablero, 'S')) {
            send(cliente_socket, "Gana el Servidor\n", strlen("Gana el Servidor\n"), 0);
            mtx.unlock();
            break;
        }
        mtx.unlock();
    }
    std::cout << "El cliente se ha desconectado" << std::endl;
    close(cliente_socket);
}

void Servidor::tablero_init(char tablero[ROW][COL]) {
    for (int f = 0; f < ROW; ++f) {
        for (int c = 0; c < COL; ++c) {
            tablero[f][c] = '-';
        }
    }
}

bool Servidor::check_winner(char tablero[ROW][COL], char jugador) {
    return check_horizontal(tablero, jugador) || check_vertical(tablero, jugador) || check_diagonal(tablero, jugador);
}

bool Servidor::check_horizontal(char tablero[ROW][COL], char jugador) {
    for (int f = 0; f < ROW; ++f) {
        for (int c = 0; c < COL - 3; ++c) {
            if (tablero[f][c] == jugador && tablero[f][c + 1] == jugador && tablero[f][c + 2] == jugador && tablero[f][c + 3] == jugador) {
                return true;
            }
        }
    }
    return false;
}

bool Servidor::check_vertical(char tablero[ROW][COL], char jugador) {
    for (int f = 0; f < ROW - 3; ++f) {
        for (int c = 0; c < COL; ++c) {
            if (tablero[f][c] == jugador && tablero[f + 1][c] == jugador && tablero[f + 2][c] == jugador && tablero[f + 3][c] == jugador) {
                return true;
            }
        }
    }
    return false;
}

bool Servidor::check_diagonal(char tablero[ROW][COL], char jugador) {
    // Diagonales hacia abajo y derecha
    for (int fila = 0; fila <= ROW - 4; fila++) {
        for (int columna = 0; columna <= COL - 4; columna++) {
            if (tablero[fila][columna] == jugador && tablero[fila + 1][columna + 1] == jugador &&
                tablero[fila + 2][columna + 2] == jugador && tablero[fila + 3][columna + 3] == jugador) {
                return true;
            }
        }
    }
    // Diagonales hacia abajo y izquierda
    for (int fila = 0; fila <= ROW - 4; fila++) {
        for (int columna = 3; columna < COL; columna++) {
            if (tablero[fila][columna] == jugador && tablero[fila + 1][columna - 1] == jugador &&
                tablero[fila + 2][columna - 2] == jugador && tablero[fila + 3][columna - 3] == jugador) {
                return true;
            }
        }
    }
    return false;
}

bool Servidor::tablero_lleno(char tablero[ROW][COL]) {
    for (int f = 0; f < ROW; ++f) {
        for (int c = 0; c < COL; ++c) {
            if (tablero[f][c] == '-') return false;
        }
    }
    return true;
}

void Servidor::imprimir_tablero(char tablero[ROW][COL]) {
    for (int f = 0; f < ROW; ++f) {
        for (int c = 0; c < COL; ++c) {
            std::cout << tablero[f][c] << '-';
        }
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        log_error("Uso incorrecto: " + std::string(argv[0]) + " <PUERTO>");
        return -1;
    }
    int puerto = std::stoi(argv[1]);
    Servidor server(puerto);
    server.run();
    return 0;
}
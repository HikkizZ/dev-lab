#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

void jugar(int sock);
void print_with_color(char c);

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <IP_SERVIDOR> <PUERTO>" << std::endl;
        return -1;
    }

    const char *server_ip = argv[1];
    int port = std::stoi(argv[2]);

    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket Error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        std::cerr << "La direccion IP no es valida" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error de Conexion" << std::endl;
        return -1;
    }

    jugar(sock);

    close(sock);
    return 0;
}

void jugar(int sock) {
    char buffer[1024] = {0};
    while (true) {
        int valread = read(sock, buffer, 1024);
        if (valread <= 0) {
            break;
        }

        system("clear");
        std::cout << "Connect4:\n";
        for (int i = 0; buffer[i] != '\0'; i++) {
            print_with_color(buffer[i]);
            if (buffer[i] == '\n') std::cout << std::endl;
        }

        if (strstr(buffer, "G") != nullptr) {
            std::cout << "[Has sido desconectado]" << std::endl;
            break;
        }

        std::cout << "Introduzca columna (1-7): ";
        std::string input;
        std::cin >> input;

        // Se toma el primer caracter ingresado, se verifica si es un número y si está en el rango 0-6
        bool valid_input = false;
        if (input.length() == 1 && isdigit(input[0])) {
            int column = input[0] - '0'; // Se convierte el caracter a entero
            if (column >= 1 && column <= 7) { // Se verifica si está en el rango 1-7
                valid_input = true;
                column--; // Se resta 1 para que esté en el rango 0-6
                input[0] = '0' + column; // Se convierte el número a caracter nuevamente
            }
        }

        if (!valid_input) {
            std::cout << "Entrada inválida. Por favor, introduzca un número entre 1 y 7." << std::endl;
            continue;
        }

        send(sock, input.c_str(), input.length(), 0);
    }
}

void print_with_color(char c) {
    switch (c) {
        case 'S':
            std::cout << "\033[1;31mS\033[0m "; // Rojo para el servidor
            break;
        case 'C':
            std::cout << "\033[1;34mC\033[0m "; // Azul para el cliente
            break;
        case '-':
            std::cout << "\033[1;32m-\033[0m "; // Verde para las casillas vacías
            break;
        default:
            std::cout << c;
            break;
    }
}

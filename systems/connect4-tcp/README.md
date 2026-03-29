# Connect Four — TCP Client/Server

A terminal-based implementation of the classic **Connect Four** game built on a Client/Server architecture using **TCP sockets** in C++.

The server supports multiple concurrent games through **multithreading**, allowing several clients to connect and play simultaneously on the same host. Communication between client and server is handled entirely over TCP, making it a practical example of network programming with POSIX sockets.

## How it works

- The **server** listens on a given port and spawns a new thread for each connected client
- The **client** connects to the server via IP and port, then interacts through the terminal
- Game state is managed server-side and synchronized with the client in real time

```bash
connect4-tcp/
├── Cliente/
│   ├── Client.cpp
│   └── Makefile
├── Servidor/
│   ├── Server.cpp
│   └── Makefile
└── README.md
```

## Requirements

- Linux
- C++ compiler with C++11 support or later

## Build & Run

**Server:**

```bash
cd Servidor/
make
./servidor <PORT>
```

**Client:**

```bash
cd Cliente/
make
./cliente <SERVER_IP> <PORT>
```

## Author

- HikkizZ
- GitHub: [https://github.com/HikkizZ](https://github.com/HikkizZ)

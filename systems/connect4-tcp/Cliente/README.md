# Cliente para Cuatro en Línea

Este directorio contiene el código fuente para el cliente del juego "Cuatro en Línea". El cliente se conecta al servidor del juego y permite a los usuarios interactuar con el juego en tiempo real, proporcionando una interfaz interactiva para jugar.

## Archivos

- `Client.cpp`: El código fuente principal para el cliente del juego.
- `Makefile`: Un Makefile para compilar el cliente fácilmente usando `make`.

## Compilación

Para compilar el cliente, asegúrate de estar en el directorio `Cliente/` y ejecuta el siguiente comando en la terminal:

```bash
make
```
Esto generará un ejecutable llamado client, que puedes usar para conectarte al servidor del juego.

## Ejecución
Para ejecutar el cliente, utiliza el siguiente comando, reemplazando <IP_SERVIDOR> con la dirección IP del servidor y <PUERTO> con el número de puerto en el que el servidor está escuchando:

```bash
./cliente <IP_SERVIDOR> <PUERTO>
```
Por ejemplo:

```bash
./cliente 127.0.0.1 7777
```
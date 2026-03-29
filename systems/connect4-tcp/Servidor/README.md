# Servidor para Cuatro en Línea

Este directorio contiene el código fuente para el servidor del juego "Cuatro en Línea". El servidor maneja las conexiones de los clientes, la lógica del juego, y asegura que el juego se ejecute de manera sincronizada entre todos los jugadores conectados.

## Archivos

- `Server.cpp`: El código fuente principal del servidor.
- `Makefile`: Un Makefile para compilar el servidor fácilmente usando `make`.

## Compilación

Para compilar el servidor, asegúrate de estar en el directorio `Servidor/` y ejecuta el siguiente comando en la terminal:

```bash
make
```
Esto generará un ejecutable llamado servidor, el cual puedes iniciar para que comience a escuchar conexiones de clientes.

## Ejecución
Para ejecutar el servidor, utiliza el siguiente comando, reemplazando <PUERTO> con el número de puerto deseado para que el servidor escuche:

```bash
./server <PUERTO>
```
'''
Código para resolver un sudoku mediante backtracking. Proyecto para ADA 2022-2.
Autor: Felipe Miranda Rebolledo

'''

#¡ Se crea una tupla para representar un nodo, donde el primer elemento es la fila y el segundo la columna
nodo = (0, 0)

# Definición de constantes
N = 9
NULO = (-1, -1)

# Tablero del sudoku
tablero = [[0 for _ in range(N)] for _ in range(N)]

# Función para leer el tablero
def leer_tablero():
    for i in range(N):
        tablero[i] = list(map(int, input().split()))
        
# Función para imprimir el tablero
def output():
    print()
    for i in range(N):
        for j in range(N):
            print(tablero[i][j], end=" ")
        print()

#¡ Función reject. Se encarga de revisar si el nodo es válido
def reject(n):
    if n[1] == -1:
        return False
    fila = n[0]
    col = n[1]
    num = tablero[fila][col]

    for i in range(N):
        if col != i and tablero[fila][i] == num:
            return True

    for i in range(N):
        if fila != i and tablero[i][col] == num:
            return True

    iFila = fila - fila % 3
    iCol = col - col % 3
    for i in range(3):
        for j in range(3):
            if ((i + iFila != fila or j + iCol != col) and tablero[i + iFila][j + iCol] == num):
                return True

    return False

#¡ Función accept. Encargada de revisar si el tablero está completo.
def accept():
    for i in range(N):
        for j in range(N):
            if tablero[i][j] == 0:
                return False
    return True

#¡ Función first nodo. Encargada de encontrar el primer nodo válido.
def first(n):
    hijo = list(n)
    if n[1] < N - 1:
        hijo[1] += 1
    elif n[0] < N - 1:
        hijo[1] = 0
        hijo[0] += 1
    else:
        hijo[1] = -1
        hijo[0] = -1
        return tuple(hijo)
    
    if tablero[hijo[0]][hijo[1]] == 0:
        tablero[hijo[0]][hijo[1]] = 1
        return tuple(hijo)
    else:
        return first(tuple(hijo))
    
#¡ Función next nodo. Busca el siguiente nodo válido.
def next(n):
    if tablero[n[0]][n[1]] < N:
        tablero[n[0]][n[1]] += 1
        return n
    else:
        tablero[n[0]][n[1]] = 0
        return NULO

#¡ Función backtracking. Encargada de realizar la busqueda recursiva.
def backtracking(n):
    if reject(n):
        return False
    if accept():
        output()
        return True
    hijo = first(n)
    while hijo != NULO:
        if backtracking(hijo):
            return True
        hijo = next(hijo)
    return False
    
# Función main
def main():
    leer_tablero()
    n = (0, -1)
    if not backtracking(n):
        print("Sin solución")

# Llamada a la función main
if __name__ == "__main__":
    main()

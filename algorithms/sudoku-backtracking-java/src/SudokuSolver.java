import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/*
    ========================================
    == P U N T O S  I M P O R T A N T E S ==
    ========================================

• Acerca del Sudoku:
    ○ El sudoku debe ser ingresado por teclado. La casilla está separada por espacios y cada linea
    por "enters".
        Ejemplo:
        0 0 3 0 0 0 0 0 0
        0 0 0 0 5 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 4 0 0
        0 0 0 0 0 0 0 4 0
        0 2 0 0 0 0 0 0 0
        0 0 0 0 7 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0

    ○ Casilla vacía será reprensentada por un 0, es decir, Sudoku[i][j] = 0.
    ○ Sudoku[i][j] = [1,...,9] significará que la casilla ha sido rellenada con un número valido hasta
    el momento.


• Restricciones (Se considera un llenado INCORRECTO del Sudoku si cumple lo siguiente)
    ○ Cualquier fila contiene el mismo número más de una vez.
    ○ Cualquier columna contiene el mismo número más de una vez.
    ○ Cualquier submatriz 3x3 contiene el mismo número más de una vez.


• El seguiento comenzará con una sub-solución y si está no nos da una respuesta final CORRECTA, entonces
regresaremos y cambiaremos la sub-solución. Los pasos serán:
    ○ Si no hay celdas sin asignar, entonces el sudoku está resuelto. Lo volvemos "True".
    ○ En caso contrario, rellenaremos una celda no asignada y si hay exito, entonces volvemos "True".
    ○ Caso contrario al anterior, cambiaremos el digito hasta que satisfaga la necesidad, en caso de no
    obtenerlo, debolvemos "False" y significara que no hay solución para el Sudoku presentado.

    ===================================
    == P U N T O S  D E L  P R O F E ==
    ===================================

• El esqueñeto del backtracking debe ser basado en:
    void backtracking(<tipo> nodo){
        if(reject(nodo)) return;
        if(accept(nodo)){
            output(); //Imprime salida
            exit(0);
        }
        <tipo> hijo = first(nodo);
        while(hijo != <nulo>){
            backtracking(hijo);
            hijo = next(hijo);
        }
    }


• Acerca del Pseudocódigo:
    ○ <tipo> debe ser definido por nosotros.
    ○ Se recomienda que la matriz debe ser variable global y que <tipo> indique la casilla actual
    en la que se está trabajando.
    ○ De manera OBLIGATORIA debemos programar reject(), accept(), first(), next().
*/
public class SudokuSolver {
    private static final int N = 9;
    private static final int UNASSIGNED = 0;

    private static boolean findUnassignedLocation(int[][] sudoku, int[] row, int[] col) {
        // Recorremos todas las casillas del tablero de Sudoku
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                // Si encontramos una casilla sin asignar, guardamos su posición y devolvemos
                // verdadero
                if (sudoku[i][j] == UNASSIGNED) {
                    row[0] = i;
                    col[0] = j;
                    return true;
                }
            }
        }
        // Si no encontramos ninguna casilla sin asignar, devolvemos falso
        return false;
    }

    private static boolean reject(int[][] sudoku, int row, int col, int num) {
        // Comprobamos si num está en la fila
        for (int i = 0; i < N; ++i) {
            if (sudoku[row][i] == num) {
                return true;
            }
        }

        // Comprobamos si num está en la columna
        for (int i = 0; i < N; ++i) {
            if (sudoku[i][col] == num) {
                return true;
            }
        }

        // Comprobamos si num está en el cuadro 3x3
        int boxRow = row - row % 3;
        int boxCol = col - col % 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (sudoku[i + boxRow][j + boxCol] == num) {
                    return true;
                }
            }
        }

        return false;
    }

    private static boolean accept(int[][] sudoku) {
        // Comprobamos si quedan casillas sin asignar
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (sudoku[i][j] == UNASSIGNED) {
                    return false;
                }
            }
        }

        return true;
    }

    private static List<Integer> first(int[][] sudoku, int row, int col) {
        List<Integer> values = new ArrayList<>();
        for (int i = 1; i <= 9; ++i) {
            if (!reject(sudoku, row, col, i)) {
                values.add(i);
            }
        }
        return values;
    }

    private static List<Integer> next(int[][] sudoku, int row, int col, int value) {
        List<Integer> values = new ArrayList<>();
        for (int i = value + 1; i <= 9; ++i) {
            if (!reject(sudoku, row, col, i)) {
                values.add(i);
            }
        }
        return values;
    }

    // Función recursiva de backtracking para resolver el sudoku
    private static boolean backtracking(int[][] sudoku) {
        // Variables para almacenar la fila y columna de la celda sin asignar
        // (Coordenadas)
        int[] row = new int[1];
        int[] col = new int[1];

        // Buscamos una celda sin asignar en el sudoku
        if (!findUnassignedLocation(sudoku, row, col)) {
            // Si no quedan celdas sin asignar, comprobamos si hemos encontrado una solución
            return accept(sudoku);
        }

        // Obtenemos la lista de valores posibles para la celda (row, col)
        List<Integer> values = first(sudoku, row[0], col[0]);
        int valueIndex = 0;
        // Mientras haya valores por probar en la lista
        while (valueIndex < values.size()) {
            // Obtenemos el próximo valor de la lista
            int num = values.get(valueIndex);
            // Comprobamos si es una asignación válida
            if (!reject(sudoku, row[0], col[0], num)) {
                // Intentamos asignar el valor num a la celda (row, col)
                sudoku[row[0]][col[0]] = num;

                // Si hemos encontrado una solución, devolvemos true
                if (backtracking(sudoku)) {
                    return true;
                }

                // Si no hemos encontrado una solución, deshacemos la asignación
                sudoku[row[0]][col[0]] = UNASSIGNED;
            }
            // Obtenemos la siguiente lista de valores posibles para la celda (row, col)
            values = next(sudoku, row[0], col[0], num);
            valueIndex = 0;
        }

        // Si no hemos encontrado una solución, devolvemos false
        return false;
    }

    private static void printSudoku(int[][] sudoku) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                System.out.print(sudoku[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Mostramos un mensaje solicitando al usuario que ingrese el tablero de Sudoku
        System.out.println("Por favor, ingrese el tablero de Sudoku de 9x9:");

        // Leemos el tablero de Sudoku de entrada
        int[][] sudoku = new int[N][N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                sudoku[i][j] = sc.nextInt();
            }
        }

        // Llamamos a la función backtracking para resolver el Sudoku
        if (backtracking(sudoku)) {
            // Si hemos encontrado una solución, mostramos un mensaje indicando que se ha
            // encontrado una solución y la imprimimos por pantalla
            System.out.println("Se ha encontrado una solución para este Sudoku:");
            printSudoku(sudoku);
        } else {
            // Si no hemos encontrado una solución, mostramos un mensaje de error
            System.out.println("No se ha encontrado una solución para este Sudoku.");
        }
    }

}
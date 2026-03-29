# Sudoku Solver — Backtracking (Java)

A Sudoku solver implemented in Java using the **backtracking algorithm**. Given a 9×9 board with empty cells, the solver explores all possible number placements and backtracks when a constraint violation is found, until a valid solution is reached or all possibilities are exhausted.

## How the algorithm works

The solver follows a classic backtracking structure built around four core operations:

* **`findUnassignedLocation`** — scans the board for the next empty cell (value `0`)
* **`reject`** — validates whether placing a number at a given cell violates any Sudoku constraint (row, column, or 3×3 box)
* **`first`** — returns all valid candidate numbers (1–9) for a given cell
* **`next`** — returns the next valid candidates after a given value, used to iterate through alternatives during backtracking

The main recursive method `backtracking` ties these together:

1. Find the next empty cell
2. Get the list of valid candidates for that cell
3. Place a candidate and recurse
4. If the recursion fails, reset the cell and try the next candidate
5. If all candidates are exhausted with no solution, return `false`
6. If no empty cells remain, the puzzle is solved

## Project Structure

```bash
sudoku-backtracking-java/
├── src/
│   └── SudokuSolver.java
├── bin/
│   └── SudokuSolver.class
├── Sudokus.txt
└── README.md
```

`Sudokus.txt` contains 3 sample puzzles with their expected solutions for testing.

## Input Format

The program reads 81 integers from stdin — 9 numbers per row, space-separated. Empty cells are represented as `0`.

Example:

```text
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

## Requirements

* Java 8 or later
* VS Code with the Java Extension Pack (optional)

## Run

```bash
cd src/
javac SudokuSolver.java -d ../bin
java -cp ../bin SudokuSolver
```

## Author

* HikkizZ
* GitHub: [https://github.com/HikkizZ](https://github.com/HikkizZ)

# Sudoku Solver — Backtracking (Python)

A Sudoku solver implemented in Python using the **backtracking algorithm**. Given a 9×9 board with empty cells, the solver explores candidate values for each empty cell and backtracks whenever a constraint violation is found.

## How the algorithm works

The solver is built around five core functions:

* **`reject(n)`** — checks if the current cell placement violates any Sudoku constraint (row, column, or 3×3 box)
* **`accept()`** — returns `True` if the board is fully filled with no empty cells
* **`first(n)`** — finds the next empty cell from the current position and sets it to `1` as the first candidate
* **`next(n)`** — increments the current cell's value to try the next candidate; returns `NULO` if all values (1–9) are exhausted, signaling a backtrack
* **`backtracking(n)`** — recursive core: rejects invalid states, accepts complete solutions, and iterates through candidates via `first` and `next`

Cell positions are represented as `(row, col)` tuples. `NULO = (-1, -1)` is used as a null marker to signal dead ends.

## Project Structure

```bash id="q1n8za"
sudoku-backtracking-py/
├── SudokuBT.py
└── README.md
```

## Requirements

* Python 3.x

## Run

```bash id="8o3m1p"
python SudokuBT.py
```

## Input Format

Enter 9 lines, each with 9 space-separated integers. Use `0` for empty cells.

Example:

```text id="x7k2lb"
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

## Author

* HikkizZ
* GitHub: <https://github.com/HikkizZ>

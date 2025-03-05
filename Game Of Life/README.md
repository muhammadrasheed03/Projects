# Conway's Game of Life

## Overview
This project simulates Conway's Game of Life, a cellular automaton devised by mathematician John Conway. The simulation takes an initial configuration of live cells and evolves the grid based on predefined rules for a given number of steps.

## Technology Used
- **Python**
- Object-Oriented Programming (OOP)

## Features
- **Grid Class**: Represents the playing surface, maintaining the state of cells.
- **Simulation Logic**:
  - Initialization of the grid with a given size.
  - Setting specific cells as alive.
  - Counting live neighbors for each cell.
  - Applying the rules of the Game of Life to transition between states.
- **Simulation Execution**: Runs for `n` steps, updating the grid after each iteration.

## Rules of Conway's Game of Life
1. Any live cell with fewer than two live neighbors dies (underpopulation).
2. Any live cell with two or three live neighbors survives.
3. Any live cell with more than three live neighbors dies (overpopulation).
4. Any dead cell with exactly three live neighbors becomes alive (reproduction).

## Usage Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/muhammadrasheed03/Projects.git
   cd Projects/GameOfLife
   ```

2. **Run the program:**
   ```bash
   python game_of_life.py
   ```

3. **Customize the simulation:**
   - Modify the list of initial live cells in the `makeCellsLive()` function.
   - Adjust the number of steps in `playGameOfLife(grid, n)`.
   
4. **Observe the output:**
   - The grid is displayed after each step, showing the evolving pattern.

## Example Initial Configuration
To simulate a simple "glider" pattern:
```python
initial_cells = [(1, 2), (2, 3), (3, 1), (3, 2), (3, 3)]
```
Modify this list to test different patterns.

## Future Improvements
- Implement graphical visualization using `matplotlib` or `pygame`.
- Support for variable grid sizes and boundary conditions.
- Save and load initial configurations from files.

Enjoy simulating Conway's Game of Life!


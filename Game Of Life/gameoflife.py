# Description of Program: simulates Conway's Game of Life. the program will take in a list of cells that are alive and then 
# simulate the game of life with any pattern for n steps. the program will output the grid after the amount of steps requested.

# constants for live and dead cells
LIVE = 'X'
DEAD = '.'

class Grid:
    """This defines the playing surface for Conway's Game of Life."""

    def __init__(self, size):
        """Create the grid as a 2D list of dimensions size x size. Initially,
        each cell of the grid contains DEAD."""
        self.size = size
        self.grid = [[DEAD for _ in range(size)] for _ in range(size)]

    def __str__(self):
        """Return a string to display when printing the grid.
        I put in an extra space between columns so that it would
        appear more square.  Don't forget to include a newline
        after each row."""
        return '\n'.join(' '.join(row) for row in self.grid) + '\n'

    def getGridSize(self):
        """Return the size of the grid."""
        return self.size

    def getCell(self, row, col):
        """Fetch the contents of the cell at coordinates (row, col).
        Assume that these are legal coordinates."""
        return self.grid[row][col]

    def setCell(self, row, col, value):
        """Set the contents of the cell at coordinates (row, col) to
        value (presumably this should be either DEAD or LIVE). 
        Assume that the coordinates are legal."""
        self.grid[row][col] = value

    def isCellLive(self, row, col):
        """A cell is live if it's within the grid and contains LIVE.
        Otherwise, it's considered DEAD. Returns 1 if alive, 0 if dead."""
        if 0 <= row < self.size and 0 <= col < self.size:
            return 1 if self.grid[row][col] == LIVE else 0
        return 0

    def countLiveNeighbors(self, row, col):
        """Count the live neighbors of the cell with coordinates (row, col).
        To do this we just need to ask of each for the 8 possible neighbors
        whether it's alive and count those that are. Return the count."""
        live_count = 0
        for dr in (-1, 0, 1):
            for dc in (-1, 0, 1):
                if (dr != 0 or dc != 0): # Skip the cell itself
                    live_count += self.isCellLive(row + dr, col + dc)
        return live_count

def makeCellsLive(grid, cellsList):
    """Given a list of coordinate pairs (x, y), make each of these
    LIVE in the grid."""
    for (row, col) in cellsList:
        grid.setCell(row, col, LIVE)

def stepGameOfLife(grid):
    """This implements one step in the Game of Life. Given a grid, update
    it following the rules of the games. For each cell, count its live 
    neighbors and decide whether it will be LIVE or DEAD in the next 
    generation."""
    size = grid.getGridSize()
    new_grid = [[DEAD for _ in range(size)] for _ in range(size)]

    for row in range(size):
        for col in range(size):
            live_neighbors = grid.countLiveNeighbors(row, col)
            if grid.getCell(row, col) == LIVE:
                if live_neighbors < 2 or live_neighbors > 3:
                    new_grid[row][col] = DEAD
                else:
                    new_grid[row][col] = LIVE
            else:
                if live_neighbors == 3:
                    new_grid[row][col] = LIVE

    for row in range(size):
        for col in range(size):
            grid.setCell(row, col, new_grid[row][col])

def playGameOfLife(grid, n):
    """Given an initial grid, take n steps in the Game of Life."""
    for _ in range(n):
        stepGameOfLife(grid)

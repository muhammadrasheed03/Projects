# Rock, Paper, Scissors Game

## Description
This is a simple command-line implementation of the classic game Rock, Paper, Scissors. The user plays against a machine, which makes a random move unless an oracle is provided as a command-line argument.

## How to Play
- The game starts with a welcome message.
- The user is prompted to select their move by entering:
  - `1` for Rock
  - `2` for Paper
  - `3` for Scissors
  - `4` to exit the game
- The machine randomly selects a move unless an oracle sequence is provided.
- The game determines the winner and updates statistics accordingly.
- When the user chooses to exit (`4`), game statistics are displayed.

## Game Rules
- Rock (`1`) beats Scissors (`3`).
- Scissors (`3`) beats Paper (`2`).
- Paper (`2`) beats Rock (`1`).
- If both players choose the same move, it is a draw.

## Running the Program
To run the game, execute the script using Python:
```sh
python rock_paper_scissors.py
```

### Using an Oracle (Optional)
You can provide a predefined sequence of moves for the machine using a command-line argument:
```sh
python rock_paper_scissors.py 12312
```
In this case, the machine will play `1` (Rock), then `2` (Paper), then `3` (Scissors), and repeat.

## Game Statistics
At the end of the game, the program displays:
- Total games played
- Number of wins, losses, and draws
- Win, loss, and draw percentages

## Example Gameplay
```
Welcome to a game of Rock, Paper, Scissors!

Choose your play:
  Enter 1 for rock;
  Enter 2 for paper;
  Enter 3 for scissors;
  Enter 4 to exit: 1
You played rock; your opponent played scissors
Congratulations, you won!

Choose your play:
  Enter 1 for rock;
  Enter 2 for paper;
  Enter 3 for scissors;
  Enter 4 to exit: 4
Game statistics:
  Games played: 1
  You won:      1 (100.0%)
  You lost:     0 (0.0%)
  No winner:    0 (0.0%)
Thanks for playing. Goodbye!
```

## Dependencies
- Python 3.x
- The `random` and `sys` modules (included in standard Python libraries)

## Author
Muhammad Yaseen Rasheed

## License
This project is for educational purposes and can be freely modified and distributed.


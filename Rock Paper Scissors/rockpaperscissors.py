
# Description of Program: This program is a simple game of Rock, Paper, Scissors. The user plays against the machine, 
# the machine's play is random
import random
import sys

# constants for game moves
ROCK = '1'
PAPER = '2'
SCISSORS = '3'

# messages
WELCOME_MESSAGE = "Welcome to a game of Rock, Paper, Scissors!"
CHOOSE_PLAY_MESSAGE = """Choose your play:
  Enter 1 for rock;
  Enter 2 for paper;
  Enter 3 for scissors;
  Enter 4 to exit: """
GOODBYE_MESSAGE = "Thanks for playing. Goodbye!"
ILLEGAL_PLAY_MESSAGE = "Illegal play entered. Try again!"
NO_GAMES_MESSAGE = "No games were completed."
STATS_MESSAGE = "Game statistics:\n  Games played: {}\n  You won:      {} ({:.1f}%)\n  You lost:     {} ({:.1f}%)\n  No winner:    {} ({:.1f}%)"

# initialize machine play settings
HAS_ORACLE = (len(sys.argv) > 1)
if HAS_ORACLE:
    MACHINE_ORACLE = sys.argv[1]
machinePlayCounter = 0

def machinePlay():
    """Returns machine's play based on oracle or randomly."""
    global machinePlayCounter
    if HAS_ORACLE and machinePlayCounter < len(MACHINE_ORACLE):
        play = MACHINE_ORACLE[machinePlayCounter]
        machinePlayCounter += 1
    else:
        play = random.choice([ROCK, PAPER, SCISSORS])
    return play

def playName(play):
    """Converts play to its string name."""
    if play == ROCK:
        return "rock"
    elif play == PAPER:
        return "paper"
    elif play == SCISSORS:
        return "scissors"
    else:
        return "unknown"

def defeats(play1, play2):
    """Returns True if play1 defeats play2."""
    return (play1 == ROCK and play2 == SCISSORS) or \
           (play1 == SCISSORS and play2 == PAPER) or \
           (play1 == PAPER and play2 == ROCK)

def printStats(plays, wins, losses, draws):
    """Prints the statistics of the game series."""
    total_games = wins + losses + draws
    if total_games == 0:
        print(NO_GAMES_MESSAGE)
    else:
        win_percentage = (wins / total_games) * 100
        loss_percentage = (losses / total_games) * 100
        draw_percentage = (draws / total_games) * 100
        print(STATS_MESSAGE.format(total_games, wins, win_percentage, losses, loss_percentage, draws, draw_percentage))

def main():
    print(WELCOME_MESSAGE)
    print()
    
    games_played = 0
    wins = 0
    losses = 0
    draws = 0
    
    while True:
        user_play = input(CHOOSE_PLAY_MESSAGE)
        
        if user_play == '4':
            printStats(games_played, wins, losses, draws)
            print(GOODBYE_MESSAGE)
            print()
            break
        elif user_play not in [ROCK, PAPER, SCISSORS]:
            print(ILLEGAL_PLAY_MESSAGE)
            print()
            continue
        
        machine_play = machinePlay()
        print(f"You played {playName(user_play)}; your opponent played {playName(machine_play)}")
        
        if user_play == machine_play:
            print("There's no winner. Try again!")
            print()
            draws += 1
        elif defeats(user_play, machine_play):
            print("Congratulations, you won!")
            print()
            wins += 1
        else:
            print("Sorry, you lost!")
            print()
            losses += 1
        
        games_played += 1


if __name__ == "__main__":
    main()

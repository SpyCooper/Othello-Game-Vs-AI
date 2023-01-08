This was a project for my Intro to Computer Science II class. The program is designed to do the following:
- The idea behind this project is that when the program is run, it creates an othello board on the terminal against an AI. (I've also heard it called Reversi, if that clarifies this)
- On the player's turn, it will display which turn it is and what the available moves are
- The AI is programmed to focus securing the corners, then walls, then other spaces on the board
- All the normal rules of othello apply: you have to flank the enemy. The game ends when either both players cannot play or when the board is full and the person with the most pieces wins
- If the player cannot make a move, they can type "XX" into the move section to skip their turn, however, a player does this and can make a move, the game will return that there is a move that can be made and ask for a move to make
- When entering a move, the letter case does not matter, so A1 and a1 will both be accepted by the program

Note: some of the code in game.h and game.cc were already made yby the teacher and were not coded by me.

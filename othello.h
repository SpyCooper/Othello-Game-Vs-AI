#ifndef OTHELLO_H
#define OTHELLO_H

#include <string>
#include <queue>
#include "game.h"
#include "piece.h"

using namespace std;

class Othello:public main_savitch_14::game
{
    public:
        Othello(); //Sets up the board for a new game
        void display_status()const; //displays the board and the current pieces
        bool is_legal(const string& move)const; //checks to see if the inputted move is a legal move
        void make_move(const string& move); //adds a new piece on the board, for part 1, it always puts an X down
        void restart(); //clears the board and puts the two O's and two X's on the board
        bool is_game_over() const; //checks to see if the game is over
        main_savitch_14::game::who winning() const; //returns who has more pieces

        //part 3 stuff
        main_savitch_14::game* clone() const; //returns the address of the copied game
        void compute_moves(std::queue<std::string>& moves) const; //pushes every possible move the current player can make
        int evaluate() const;
    
    private:
        Piece board[8][8];
        int skipsToEnd;
};

#endif
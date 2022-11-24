#ifndef Piece_H
#define Piece_H

#include <string>

using namespace std;

class Piece
{
    public:
        Piece() {side = ' ';} //sets the piece to a black space
        void clear() {side = ' ';} //sets the side to be blank
        void set_side(char s) {side = s;} //sets the spot to an X or an O
        void flip() {if(side == 'X') side = 'O'; else if(side == 'O') side = 'X';} //turns an X to an O or an O to an X
        char get_side()const {return side;} //returns the current side

    private:
        char side;
};

#endif
#ifndef OTHELLO_CC
#define OTHELLO_CC

#include <string>
#include <iostream>
#include <cctype>
#include <queue>
#include "colors.h"
#include "othello.h"
#include "game.h"

using namespace std;

Othello::Othello()
{
    //calls restart, since it sets up the board for a new game
    restart();
}

void Othello::display_status()const
{
    //sets up the border for the positions on the top of the board
    cout << WHITE << B_GREEN << "   | A | B | C | D | E | F | G | H |   " << RESET << endl;
    for(int i = 0; i < 8; i++)
    {
        cout << WHITE << B_GREEN << " ------------------------------------- " << RESET << endl;

        //sets up the numbers on the left side of the board
        cout << WHITE << B_GREEN << " " << i+1 << " " << RESET;

        //displays the spots and pieces on the board
        for(int j = 0; j < 8; j++)
        {
            cout << WHITE << B_GREEN << "|" << RESET;
            if(board[i][j].get_side() == 'X')
            {
                cout << WHITE << B_BLACK << " " << board[i][j].get_side() << " " << RESET;
            }
            else if(board[i][j].get_side() == 'O')
            {
                cout << BLACK << B_WHITE << " " << board[i][j].get_side() << " " << RESET;
            }
            else
            {
                cout << WHITE << B_GREEN << " " << board[i][j].get_side() << " " << RESET;
            }
        }

        //sets up the numbers on the right side of the board
        cout << WHITE << B_GREEN << "| " << i+1 << " " << RESET << endl;
    }
    cout << WHITE << B_GREEN << " ------------------------------------- " << RESET  << endl;

    //sets up the border for the positions on the bottom of the board
    cout << WHITE << B_GREEN << "   | A | B | C | D | E | F | G | H |   " << RESET << endl;
}

bool Othello::is_legal(const string& move)const
{
    //sets who's move it is
    char currentMove = ' ';
    if(last_mover() == HUMAN)
    {
        currentMove = 'O';
    }
    else
    {
        currentMove = 'X';
    }
    if(move == "XX" || move == "xx" || move == "xX" || move == "Xx")
    {
        for(int t = 'A'; t <= 'H'; t++)
        {
            for(int s = '1'; s <= '8'; s++)
            {
                string temp;
                temp.push_back(t);
                temp.push_back(s);
                if(is_legal(temp))
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        char t = move.at(0);
        if(islower(t))
            t = toupper(t);
        char u = move.at(1);
        //checks to make sure the move is an actual spot on the board
        if(t < 'A' || t > 'H')
            return false;
        if(u < '1' || u > '8')
            return false;
        
        //converts the move into a readable position in the 2D array
        int top = -1;
        int side = -1;
        //changes the char to a int for the position in the 2D array
        if(t == 'A')
            top = 0;
        else if( t =='B')
            top = 1;
        else if( t =='C')
            top = 2;
        else if( t =='D')
            top = 3;
        else if( t =='E')
            top = 4;
        else if( t =='F')
            top = 5;
        else if( t =='G')
            top = 6;
        else if( t =='H')
            top = 7;
        
        //changes the char to a int for the position in the 2D array
        if(u == '1')
            side = 0;
        else if(u == '2')
            side = 1;
        else if(u == '3')
            side = 2;
        else if(u == '4')
            side = 3;
        else if(u == '5')
            side = 4;
        else if(u == '6')
            side = 5;
        else if(u == '7')
            side = 6;
        else if(u == '8')
            side = 7;
        
        //checks to see if there is already a piece in the position entered
        if(board[side][top].get_side() != ' ')
            return false;

        //checks the row it wants to be placed in
        for(int i = top+1; i < 8; i ++)
        {
            if(board[side][i].get_side() == currentMove && board[side][top+1].get_side() != currentMove)
            {
                return true;
                break;
            }
            else if(board[side][i].get_side() == ' ')
                break;
        }
        for(int i = top-1; i > -1; i--)
        {
            if(board[side][i].get_side() == currentMove && board[side][top-1].get_side() != currentMove)
            {
                return true;
                break;
            }
            else if(board[side][i].get_side() == ' ')
                break;
        }
        //checks the column it wants to be placed in
        for(int i = side+1; i < 8; i ++)
        {
            if(board[i][top].get_side() == currentMove && board[side+1][top].get_side() != currentMove)
            {
                return true;
                break;
            }
            else if(board[i][top].get_side() == ' ')
                break;
        }
        for(int i = side-1; i > -1; i--)
        {
            if(board[i][top].get_side() == currentMove && board[side-1][top].get_side() != currentMove)
            {
                return true;
                break;
            }
            else if(board[i][top].get_side() == ' ')
                break;
        }

        //checks diagonally to the top left
        int count = 1;
        if(side != 0 && top != 0)
        {
            while(side-count != -1 && top-count != -1)
            {
                if(board[side-count][top-count].get_side() == currentMove && board[side-1][top-1].get_side() != currentMove)
                {
                    return true;
                    break;
                }
                else if(board[side-count][top-count].get_side() == ' ')
                    break;
                count++;
            }
        }

        //checks diagonally to the bottom left
        count = 1;
        if(side != 7 && top != 7)
        {
            while(side+count != 8 && top+count != 8)
            {
                if(board[side+count][top+count].get_side() == currentMove && board[side+1][top+1].get_side() != currentMove)
                {
                    return true;
                    break;
                }
                else if(board[side+count][top+count].get_side() == ' ')
                    break;
                count++;
            }
        }

        //checks diagonally to the bottom right
        count = 1;
        if(side != 7 && top != 0)
        {
            while(side+count != 8 && top-count != -1)
            {
                if(board[side+count][top-count].get_side() == currentMove && board[side+1][top-1].get_side() != currentMove)
                {
                    return true;
                    break;
                }
                else if(board[side+count][top-count].get_side() == ' ')
                    break;
                count++;
            }
        }

        //checks diagonally to the top right
        count = 1;
        if(side != 0 && top != 7)
        {
            while(side-count >= -1 && top+count <= 8)
            {
                if(board[side+-count][top+count].get_side() == currentMove && board[side-1][top+1].get_side() != currentMove)
                {
                    return true;
                    break;
                }
                else if(board[side+-count][top+count].get_side() == ' ')
                    break;
                count++;
            }
        }
    }
    return false;
}

void Othello::make_move(const string& move)
{
    //skips is XX is entered and the player has no moves
    if(move == "XX")
    {
        if(evaluate() < 0)
        {
            game::make_move(move);
            skipsToEnd++;
            return;
        }
        game::make_move(move);
        skipsToEnd++;
        return;
    }
    
    //sets who's move it is
    char currentMove = ' ';
    if(last_mover() == HUMAN)
    {
        currentMove = 'O';
        skipsToEnd = 0;
    }
    else
    {
        currentMove = 'X';
        skipsToEnd = 0;
    }

    char t = move.at(0);
    if(islower(t))
        t = toupper(t);
    char u = move.at(1);
    //converts the move into a readable position in the 2D array
    int top = -1;
    int side = -1;
    //changes the char to a int for the position in the 2D array
    if(t == 'A')
        top = 0;
    else if( t =='B')
        top = 1;
    else if( t =='C')
        top = 2;
    else if( t =='D')
        top = 3;
    else if( t =='E')
        top = 4;
    else if( t =='F')
        top = 5;
    else if( t =='G')
        top = 6;
    else if( t =='H')
        top = 7;
    
    //changes the char to a int for the position in the 2D array
    if(u == '1')
        side = 0;
    else if(u == '2')
        side = 1;
    else if(u == '3')
        side = 2;
    else if(u == '4')
        side = 3;
    else if(u == '5')
        side = 4;
    else if(u == '6')
        side = 5;
    else if(u == '7')
        side = 6;
    else if(u == '8')
        side = 7;
    
    //puts an X on the valid moves
    board[side][top].set_side(currentMove);

    //flips horizontally
    bool horRight = false;
    int count = 1;
    while(top+count <= 7)
    {
        if(board[side][top+count].get_side() == ' ')
        {
            break;
        }
        else if(board[side][top+count].get_side() == currentMove)
        {
            if(count != 1)
            {
                horRight = true;
            }
            break;
        }
        count++;
    }
    bool horleft = false;
    count = 1;
    while(top-count >= 0)
    {
        if(board[side][top-count].get_side() == ' ')
        {
            break;
        }
        else if(board[side][top-count].get_side() == currentMove)
        {
            if(count != 1)
            {
                horleft = true;
            }
            break;
        }
        count++;
    }
    count = 1;
    if(horRight)
    {
        while(top+count <= 7)
        {
            if(board[side][top+count].get_side() == currentMove)
            {
                break;
            }
            else
            {
                board[side][top+count].flip();
            }
            count++;
        }
    }
    count = 1;
    if(horleft)
    {
        while(top-count >= 0)
        {
            if(board[side][top-count].get_side() == currentMove)
            {
                break;
            }
            else
            {
                board[side][top-count].flip();
            }
            count++;
        }
    }

    //flips vertically
    bool vertDown = false;
    count = 1;
    while(side+count <= 7)
    {
        if(board[side+count][top].get_side() == ' ')
        {
            break;
        }
        else if(board[side+count][top].get_side() == currentMove)
        {
            if(count != 1)
                vertDown = true;
            break;
        }
        count++;
    }
    bool vertUp = false;
    count = 1;
    while(side-count >= 0)
    {
        if(board[side-count][top].get_side() == ' ')
        {
            break;
        }
        else if(board[side-count][top].get_side() == currentMove)
        {
            if(count != 1)
                vertUp = true;
            break;
        }
        count++;
    }
    count = 1;
    if(vertDown)
    {
        while(side+count <= 7)
        {
            if(board[side+count][top].get_side() == currentMove)
            {
                break;
            }
            else
            {
                board[side+count][top].flip();
            }
            count++;
        }
    }
    count = 1;
    if(vertUp)
    {
        while(side-count >= 0)
        {
            if(board[side-count][top].get_side() == currentMove)
            {
                break;
            }
            else
            {
                board[side-count][top].flip();
            }
            count++;
        }
    }

    //checks diagonally to the top left and flips until it hits a similar piece
    bool topLeft = false;
    count = 1;
    if(side != 0 && top != 0)
    {
        while(side-count >= 0 && top-count >= 0)
        {
            if(board[side-count][top-count].get_side() == currentMove)
            {
                if(count != 1)
                    topLeft = true;
                break;
            }
            else if(board[side-count][top-count].get_side() == ' ')
            {
                break;
            }
            count++;
        }
    }
    count = 1;
    if(topLeft)
    {
        while(side-count >= 0 && top-count >= 0)
        {
            if(board[side-count][top-count].get_side() == currentMove)
            {
                break;
            }
            else
            {
                board[side-count][top-count].flip();
            }
            count++;
        }
    }

    //checks diagonally to the bottom left and flips until a similar piece
    bool botRight = false;
    count = 1;
    if(side != 7 && top != 7)
    {
        while(side+count <= 7 && top+count <= 7)
        {
            if(board[side+count][top+count].get_side() == currentMove)
            {
                if(count != 1)
                    botRight = true;
                break;
            }
            else if(board[side+count][top+count].get_side() == ' ')
            {
                break;
            }
            count++;
        }
    }
    count = 1;
    if(botRight)
    {
        while(side+count <= 7 && top+count <= 7)
        {
            if(board[side+count][top+count].get_side() == currentMove)
            {
                break;
            }
            else
            {
                board[side+count][top+count].flip();
            }
            count++;
        }
    }

    //checks diagonally to the bottom right and flips until it sees a similar piece
    bool botLeft = false;
    count = 1;
    if(side != 7 && top != 0)
    {
        while(side+count <= 7 && top-count >= 0)
        {
            if(board[side+count][top-count].get_side() == currentMove)
            {
                if(count != 1)
                    botLeft = true;
                break;
            }
            else if(board[side+count][top-count].get_side() == ' ')
            {
                break;
            }
            count++;
        }
    }
    count = 1;
    if(botLeft)
    {
        while(side+count <= 7 && top-count >= 0)
        {
            if(board[side+count][top-count].get_side() == currentMove)
            {
                break;
            }
            else
            {
                board[side+count][top-count].flip();
            }
            count++;
        }
    }

    //checks diagonally to the top right
    count = 1;
    bool topRight = false;
    if(side != 0 && top != 7)
    {
        while(side-count >= 0 && top+count <= 7)
        {
            if(board[side-count][top+count].get_side() == currentMove)
            {
                if(count != 1)
                    topRight = true;
                break;
            }
            else if(board[side-count][top+count].get_side() == ' ')
            {
                break;
            }
            count++;
        }
    }
    count = 1;
    if(topRight)
    {
        while(side-count >= 0 && top+count <= 7)
        {
            if(board[side-count][top+count].get_side() == currentMove)
            {
                break;
            }
            else
            {
                board[side-count][top+count].flip();
            }
            count++;
        }
    }

    game::make_move(move);
}

void Othello::restart()
{
    //goes through every position and clears it.
    for(int i = 0; i < 8; i ++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j].clear();
        }
    }

    //puts the 2 X's and O's in the middle to start a game
    board[3][3].set_side('O');
    board[4][4].set_side('O');
    board[3][4].set_side('X');
    board[4][3].set_side('X');

    skipsToEnd = 0;
    game::restart();
}

bool Othello::is_game_over()const
{
    //ends if both players skip
    if(skipsToEnd == 2)
    {
        return true;
    }

    //ends if the board is full 
    bool bFull = true;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j].get_side() == ' ')
                bFull = false;
        }
    }
    if(bFull)
        return bFull;
    return false;
}

main_savitch_14::game::who Othello::winning() const
{
    int black = 0;
    int white = 0;
    for(int i = 0; i < 8; i ++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j].get_side() == 'X')
            {
                black++;
            }
            else if(board[i][j].get_side() == 'O')
            {
                white++;
            }
        }
    }

    if(black > white)
        return HUMAN;
    else if(white > black)
        return COMPUTER;
    return NEUTRAL;
}

main_savitch_14::game* Othello::clone() const
{
    return new Othello(*this);
}

void Othello::compute_moves(queue<string>& moves) const
{
    for(int t = 'A'; t <= 'H'; t++)
    {
        for(int s = '1'; s <= '8'; s++)
        {
            string temp;
            temp.push_back(t);
            temp.push_back(s);
            if(is_legal(temp))
            {
                moves.push(temp);
            }
        }
    }
    if(moves.empty())
    {
        moves.push("XX");
    }
}

int Othello::evaluate()const
{
    int numOfPieces = 0;
    char currentMove = ' ';
    char otherMove = ' ';
    if(last_mover() == HUMAN)
    {
        currentMove = 'O';
        otherMove = 'X';
    }
    else
    {
        currentMove = 'X';
        otherMove = 'O';
    }
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j].get_side() == currentMove)
            {
                if(i == 0 && j == 0)
                    numOfPieces+=3;
                else if(i == 0 && j == 8)
                    numOfPieces+=3;
                else if(i == 8 && j == 8)
                    numOfPieces+=3;
                else if(i == 8 && j == 0)
                    numOfPieces+=3;
                else if(i == 0 || j == 0)
                    numOfPieces+=2;
                else if(i == 8 || j == 8)
                    numOfPieces+=2;
                else
                    numOfPieces++;
            }
            else if(board[i][j].get_side() == otherMove)
            {
                if(i == 0 && j == 0)
                    numOfPieces-=3;
                else if(i == 8 && j == 0)
                    numOfPieces-=3;
                else if(i == 0 && j == 8)
                    numOfPieces-=3;
                else if(i == 8 && j == 8)
                    numOfPieces-=3;
                else if(i == 0 || j == 0)
                    numOfPieces-=2;
                else if(i == 8 || j == 8)
                    numOfPieces-=2;
                else
                    numOfPieces--;
            }
        }
    }
    return numOfPieces;
}
#endif
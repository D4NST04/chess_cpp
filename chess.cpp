#include <iostream>
#include "helpers.h"
#include "chess.h"
#include "gameManager.h"

void Piece::disactivate()
{
    isActive = false;
    x = -1;
    y = -1;
}

//empty pieces should be innactive
Piece::Piece()
{
    display = ' ';
    isActive = false;
}

Piece::Piece(int x_, int y_, bool isWhite_)
{
    x = x_;
    y = y_;
    isWhite = isWhite_;
    isActive = true;
}

Queen::Queen(int x_, int y_, bool white) : Piece(x_, y_, white)
{
    display = 'H';
    points = 9;
}

int **Queen ::Update(GameManager *gm, int **board)
{

    int **possibleMoves = getArray(8);

    for (int i = this->x + 1; i < 8; i++)
    {
        if (board[i][this->y] != 0)
        {
            if (gm->getPieceAt(i, this->y)->isWhite == this->isWhite)
            {
                //0 if theres an ally
                possibleMoves[i][this->y] = 0;
                break;
            }
            //2 if theres an enemy
            else
            {
                possibleMoves[i][this->y] = 2;
                break;
            }
        }
        else
            possibleMoves[i][this->y] = 1;
    }

    for (int i = this->x - 1; i >= 0; i--)
    {
        if (board[i][this->y] != 0)
        {
            if (gm->getPieceAt(i, this->y)->isWhite == this->isWhite)
            {
                //0 if theres an ally
                possibleMoves[i][this->y] = 0;
                break;
            }
            //2 if theres an enemy
            else
            {
                possibleMoves[i][this->y] = 2;
                break;
            }
        }
        else
            possibleMoves[i][this->y] = 1;
    }

    for (int i = this->y + 1; i < 8; i++)
    {
        if (board[this->x][i] != 0)
        {
            if (gm->getPieceAt(this->x, i)->isWhite == this->isWhite)
            {
                //0 if theres an ally
                possibleMoves[this->x][i] = 0;
                break;
            }
            //2 if theres an enemy
            else
            {
                possibleMoves[this->x][i] = 2;
                break;
            }
        }
        else
            possibleMoves[this->x][i] = 1;
    }

    for (int i = this->y - 1; i >= 0; i--)
    {
        if (board[this->x][i] != 0)
        {
            if (gm->getPieceAt(this->x, i)->isWhite == this->isWhite)
            {
                //0 if theres an ally
                possibleMoves[this->x][i] = 0;
                break;
            }
            //2 if theres an enemy
            else
            {
                possibleMoves[this->x][i] = 2;
                break;
            }
        }
        else
            possibleMoves[this->x][i] = 1;
    }

    int x = this->x + 1;
    int y = this->y + 1;
    while (y < 8 && x < 8)
    {
        if (board[x][y] != 0)
        {
            if (gm->getPieceAt(x, y)->isWhite == this->isWhite)
            {
                //0 if theres an ally
                possibleMoves[x][y] = 0;
                break;
            }
            //2 if theres an enemy
            else
            {
                possibleMoves[x][y] = 2;
                break;
            }
        }
        else
            possibleMoves[x][y] = 1;
        x++;
        y++;
    }
    x = this->x - 1;
    y = this->y - 1;
    while (y >= 0 && x >= 0)
    {
        if (board[x][y] != 0)
        {
            if (gm->getPieceAt(x, y)->isWhite == this->isWhite)
            {
                //0 if theres an ally
                possibleMoves[x][y] = 0;
                break;
            }
            //2 if theres an enemy
            else
            {
                possibleMoves[x][y] = 2;
                break;
            }
        }
        else
            possibleMoves[x][y] = 1;
        x--;
        y--;
    }
    x = this->x - 1;
    y = this->y + 1;
    while (y < 8 && x >= 0)
    {
        if (board[x][y] != 0)
        {
            if (gm->getPieceAt(x, y)->isWhite == this->isWhite)
            {
                //0 if theres an ally
                possibleMoves[x][y] = 0;
                break;
            }
            //2 if theres an enemy
            else
            {
                possibleMoves[x][y] = 2;
                break;
            }
        }
        else
            possibleMoves[x][y] = 1;
        x--;
        y++;
    }
    x = this->x + 1;
    y = this->y - 1;
    while (y >= 0 && x < 8)
    {
        if (board[x][y] != 0)
        {
            if (gm->getPieceAt(x, y)->isWhite == this->isWhite)
            {
                //0 if theres an ally
                possibleMoves[x][y] = 0;
                break;
            }
            //2 if theres an enemy
            else
            {
                possibleMoves[x][y] = 2;
                break;
            }
        }
        else
            possibleMoves[x][y] = 1;
        x++;
        y--;
    }
    possibleMoves[this->x][this->y] = 0;

    return possibleMoves;
};


Pawn::Pawn(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
    display = 'P';
    points = 1;
}

int** Pawn::Update(GameManager* gm, int** board)
{
    int** possibleMoves = getArray(8);

    if(this->isWhite){
        if(this->y == 6){
            if(board[x][y-1] == 0 && board[x][y-2] == 0){
                possibleMoves[x][y-1]=1;
                possibleMoves[x][y-2]=1;
            }
            else if(board[x][y-1] == 0 && board[x][y-2] == 1){
                possibleMoves[x][y-1]=1;
            }
        }
        if(board[x][y-1] == 0){
            possibleMoves[x][y-1]=1;
        }
        if(this->x == 0){
                 if(gm->getPieceAt(x+1, y-1)->isWhite != this->isWhite && board[x+1][y-1] != 0){
                        possibleMoves[x+1][y-1] = 2;
                 }
        }
        if(this->x == 7){
                 if(gm->getPieceAt(x-1, y-1)->isWhite != this->isWhite && board[x-1][y-1] != 0){
                        possibleMoves[x-1][y-1] = 2;
                 }
        }
        if(this->x >= 1 && this->x <= 6){
                if(gm->getPieceAt(x+1, y-1)->isWhite != this->isWhite && board[x+1][y-1] != 0){
                        possibleMoves[x+1][y-1]=2;
                }
                if(gm->getPieceAt(x-1, y-1)->isWhite != this->isWhite && board[x-1][y-1] != 0){
                        possibleMoves[x-1][y-1]=2;
                }
        }
    }else{

        if(this->y == 1){
            if(board[x][y+1] == 0 && board[x][y+2] == 0){
                possibleMoves[x][y+1]=1;
                possibleMoves[x][y+2]=1;
            }
            else if(board[x][y+1] == 0 && board[x][y+2] == 1){
                possibleMoves[x][y+1]=1;
            }
        }
        if(board[x][y+1] == 0){
            possibleMoves[x][y+1]=1;
        }
        if(this->x == 0){
                if(gm->getPieceAt(x+1, y+1)->isWhite != this->isWhite){
                        possibleMoves[x+1][y+1]=2;
                }
        }
        if(this->x == 7){
                 if(gm->getPieceAt(x-1, y+1)->isWhite != this->isWhite){
                        possibleMoves[x-1][y+1]=2;
                }
        }
        if(this->x >= 1 && this->x <= 6){
                if(gm->getPieceAt(x+1, y+1)->isWhite != this->isWhite){
                        possibleMoves[x+1][y+1]=2;
                }
                if(gm->getPieceAt(x-1, y+1)->isWhite != this->isWhite){
                        possibleMoves[x-1][y+1]=2;
                }
        }
}

    return possibleMoves;
};


King::King(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
    display = 'K';
    points = -1;
}

King::~King() {}

int **King::Update(GameManager *gm, int **board)
{
    int **possibleMoves = getArray(8);

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue;

            int newX = x + i;
            int newY = y + j;

            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
            {
                Piece *targetPiece = gm->getPieceAt(newX, newY);
                int **is_attacked = isWhite ? gm->attackBoardBlack : gm->attackBoardWhite;

                if (board[newX][newY] == 0 && !is_attacked[newX][newY])
                {
                    possibleMoves[newX][newY] = 1;
                }
                else if (targetPiece->isWhite != this->isWhite && !is_attacked[newX][newY])
                {
                    possibleMoves[newX][newY] = 2;
                }
            }
        }
    }

    return possibleMoves;
}

Rook::Rook(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
    display = 'W';
    points = 5;
}

int **Rook::Update(GameManager *gm, int **board)
{
    int **possibleMoves = getArray(8);

    for (int y = this->y + 1; y < 8; y++)
    {
        if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else if (gm->getPieceAt(x, y)->isWhite == this->isWhite)
        {
            break;
        }
        else
        {
            possibleMoves[x][y] = 2;
            break;
        }
    }

    for (int x = this->x + 1; x < 8; x++)
    {
        if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else if (gm->getPieceAt(x, y)->isWhite == this->isWhite)
        {
            break;
        }
        else
        {
            possibleMoves[x][y] = 2;
            break;
        }
    }

    for (int x = this->x - 1; x >= 0; x--)
    {
        if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else if (gm->getPieceAt(x, y)->isWhite == this->isWhite)
        {
            break;
        }
        else
        {
            possibleMoves[x][y] = 2;
            break;
        }
    }

    for (int y = this->y - 1; y >= 0; y--)
    {
        if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else if (gm->getPieceAt(x, y)->isWhite == this->isWhite)
        {
            break;
        }
        else
        {
            possibleMoves[x][y] = 2;
            break;
        }
    }
    return possibleMoves;
};

Bishop::Bishop(int x_, int y_, bool isWhite_) : Piece(x_, y_, isWhite_)
{
    display = 'G';
    points = 3;
}

int **Bishop::Update(GameManager *gm, int **board)
{
    int **possibleMoves = getArray(8);

    // Check moves in the positive x, positive y direction
    for (int i = 1; this->x + i < 8 && this->y + i < 8; i++)
    {
        if (board[this->x + i][this->y + i] == 0)
        {
            possibleMoves[this->x + i][this->y + i] = 1;
        }
        else if (gm->getPieceAt(this->x + i, this->y + i)->isWhite != this->isWhite)
        {
            possibleMoves[this->x + i][this->y + i] = 2;
            break;
        }
        else
        {
            break;
        }
    }

    // Check moves in the positive x, negative y direction
    for (int i = 1; this->x + i < 8 && this->y - i >= 0; i++)
    {
        if (board[this->x + i][this->y - i] == 0)
        {
            possibleMoves[this->x + i][this->y - i] = 1;
        }
        else if (gm->getPieceAt(this->x + i, this->y - i)->isWhite != this->isWhite)
        {
            possibleMoves[this->x + i][this->y - i] = 2;
            break;
        }
        else
        {
            break;
        }
    }

    // Check moves in the negative x, positive y direction
    for (int i = 1; this->x - i >= 0 && this->y + i < 8; i++)
    {
        if (board[this->x - i][this->y + i] == 0)
        {
            possibleMoves[this->x - i][this->y + i] = 1;
        }
        else if (gm->getPieceAt(this->x - i, this->y + i)->isWhite != this->isWhite)
        {
            possibleMoves[this->x - i][this->y + i] = 2;
            break;
        }
        else
        {
            break;
        }
    }

    // Check moves in the negative x, negative y direction
    for (int i = 1; this->x - i >= 0 && this->y - i >= 0; i++)
    {
        if (board[this->x - i][this->y - i] == 0)
        {
            possibleMoves[this->x - i][this->y - i] = 1;
        }
        else if (gm->getPieceAt(this->x - i, this->y - i)->isWhite != this->isWhite)
        {
            possibleMoves[this->x - i][this->y - i] = 2;
            break;
        }
        else
        {
            break;
        }
    }

    return possibleMoves;
}


Knight::Knight(int x_, int y_, bool isWhite_) : Piece(x_, y_, isWhite_)
{
    display = 'K';
    points =3;
}

int** Knight::Update(GameManager* gm, int** board) {
    int** possibleMoves = getArray(8);

    // Knight moves in an L-shape pattern
    int moveOffsets[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                             {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int i = 0; i < 8; ++i) {
        int newX = x + moveOffsets[i][0];
        int newY = y + moveOffsets[i][1];

        if (newX >= 0 && newY >= 0 && newX < 8 && newY < 8) {
            if (board[newX][newY] == 0 || gm->getPieceAt(newX, newY)->isWhite != isWhite) {
                possibleMoves[newX][newY] = 1;
            }
        }
    }

    return possibleMoves;
}



/*
int **Knight::Update(GameManager *gm, int **board)
{
    int **possibleMoves = getArray(8);
    return possibleMoves;
    
     KONIECZNIE POPRAWIC, NAWET SIE NIE
    int x = this->x + 1;
    int y = this->y + 2;
    int colorCheck = 17;
    if (x < 8 && y < 8)
    {
        if (this->isWhite)
            colorCheck = 1;
        if (board[x][y] >= colorCheck && board[x][y] <= (colorCheck + 15))
        {
            ;
        }
        else if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else
        {
            possibleMoves[x][y] = 2;
        }
    }
    int x = this->x + 2;
    int y = this->y + 1;
    int colorCheck = 17;
    if (x < 8 && y < 8)
    {
        if (this->isWhite)
            colorCheck = 1;
        if (board[x][y] >= colorCheck && board[x][y] <= (colorCheck + 15))
        {
            ;
        }
        else if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else
        {
            possibleMoves[x][y] = 2;
        }
    }
    int x = this->x - 2;
    int y = this->y + 1;
    int colorCheck = 17;
    if (x >= 0 && y <= 8)
    {
        if (this->isWhite)
            colorCheck = 1;
        if (board[x][y] >= colorCheck && board[x][y] <= (colorCheck + 15))
        {
            ;
        }
        else if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else
        {
            possibleMoves[x][y] = 2;
        }
    }
    int x = this->x - 1;
    int y = this->y + 2;
    int colorCheck = 17;
    if (x >= 0 && y <= 8)
    {
        if (this->isWhite)
            colorCheck = 1;
        if (board[x][y] >= colorCheck && board[x][y] <= (colorCheck + 15))
        {
            ;
        }
        else if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else
        {
            possibleMoves[x][y] = 2;
        }
    }
    int x = this->x + 1;
    int y = this->y - 2;
    int colorCheck = 17;
    if (x =< 8 &&y >= 0)
    {
        if (this->isWhite)
            colorCheck = 1;
        if (board[x][y] >= colorCheck && board[x][y] <= (colorCheck + 15))
        {
            ;
        }
        else if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else
        {
            possibleMoves[x][y] = 2;
        }
    }
    int x = this->x + 2;
    int y = this->y - 1;
    int colorCheck = 17;
    if (x <= 8 &&y >= 0)
    {
        if (this->isWhite)
            colorCheck = 1;
        if (board[x][y] >= colorCheck && board[x][y] <= (colorCheck + 15))
        {
            ;
        }
        else if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else
        {
            possibleMoves[x][y] = 2;
        }
    }
    int x = this->x - 1;
    int y = this->y - 2;
    int colorCheck = 17;
    if (x >= 0 &&y >= 0)
    {
        if (this->isWhite)
            colorCheck = 1;
        if (board[x][y] >= colorCheck && board[x][y] <= (colorCheck + 15))
        {
            ;
        }
        else if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else
        {
            possibleMoves[x][y] = 2;
        }
    }
    int x = this->x - 2;
    int y = this->y - 1;
    int colorCheck = 17;
    if (x >= 0 &&y  >= 0)
    {
        if (this->isWhite)
            colorCheck = 1;
        if (board[x][y] >= colorCheck && board[x][y] <= (colorCheck + 15))
        {
            ;
        }
        else if (board[x][y] == 0)
        {
            possibleMoves[x][y] = 1;
        }
        else
        {
            possibleMoves[x][y] = 2;
        }
    }
    possibleMoves[this->x][this->y] = 0;

    return possibleMoves;

}*/

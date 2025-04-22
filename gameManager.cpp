#include "gameManager.h"
#include "helpers.h"
#include "chess.h"

Piece *GameManager::getPieceAt(int x, int y)
{
    return board[id_board[x][y]];
}

bool GameManager::isEmptyPiece(Piece *p) {return p->display == ' ';}

//checks if pawn made it to the end of the chessboard.
void GameManager::pawnPromo(Piece *p){

    if (p->isWhite && p->y == 0){
        cout << "Wybierz figure na miejsce pionka(";
        for(int i = 1; i< 33; i++){

            if(isEmptyPiece(board[i]) || board[i]->isActive)
                continue;
            cout << board[i]->display;
        }
        cout << "): ";
        char symbol;
        cin >> symbol;

        for(int i = 1; i < 33; i++){
            if(board[i]->display == symbol && board[i]->isWhite){
                
            board[i]->x = p->x;
            board[i]->y = p ->y;

            id_board[p->x][p->y] = i;
            board[i]->isActive = true;
            p->isActive = false;

            }
               
        }

    }
    else if (!p->isWhite && p->y == 7){
        cout << "Wybierz figure na miejsce pionka(";
        for(int i = 1; i< 33; i++){

            if(isEmptyPiece(board[i]) || board[i]->isActive)
                continue;
            cout << board[i]->display;
        }
        cout << "): ";
        char symbol;
        cin >> symbol;

        for(int i = 1; i < 33; i++){
            if(board[i]->display == symbol && !board[i]->isWhite){
                
            board[i]->x = p->x;
            board[i]->y = p ->y;

            id_board[p->x][p->y] = i;
            board[i]->isActive = true;
            p->isActive = false;

            }
               
        }      
    }
}

void GameManager::proceed_turn()
{

    Piece *p;
    bool made_move = false;
    while (!made_move)
    {
        //temp.
        cout << "Wybierz figure:" << endl;
        int x, y;
        cin >> x;
        if(x == -1) { selectedPiece = -1; printBoard(); cout << "Anulowano." ;  continue;}

        cin >> y;
        if(y == -1) {selectedPiece = -1; printBoard(); cout << "Anulowano." ; continue;}

        x--;
        y--;
        p = getPieceAt(x,y);
        if (p->display == ' ')
        {
            cout << "Puste pole. ";
            continue;
        }
        else if (p->isWhite != isTurnWhite)
        {
            cout << "Pion innego koloru. ";
            continue;
        }
        selectedPiece = id_board[x][y];
        printBoard();

        cout << "Pole docelowe:" << endl;
        int destX, destY;

        cin >> destX;
        if(destX == -1) {selectedPiece = -1;printBoard(); cout << "Anulowano.";  ;continue;}

        cin >> destY;
        if(destY == -1) {selectedPiece = -1;printBoard(); cout << "Anulowano."; selectedPiece = -1;;continue;}

        destX--;
        destY--;
        made_move = movePiece(p, destX, destY);

        //check for pawn promotion
        if(p->display == 'P')
            pawnPromo(p);
        
        if (!made_move) cout << "Nie mozesz udac sie na to pole. ";
    }

    isTurnWhite = !isTurnWhite;
}


//Todo: GameManager could loop through board array. 
//That way we dont have to iterate over empty fields. too bad i didnt think it through while first implementing.
void GameManager::printBoard()
{
    int **moves;
    if (selectedPiece != -1)
        moves = board[selectedPiece]->Update(this, id_board);


    int pointsW = 0, pointsB = 0;
    cout << "Zbite: " << endl;;
    for (int x =  1; x < 33; x++){
        //we search for pieces that are innactive and are not empty pieces.
        if (!isEmptyPiece(board[x]) && !board[x]->isActive && board[x]->isWhite){
            pointsW += board[x]->points;
            cout<< RED << board[x]->display << " " << RESET;
        }
    }
    cout << "(" << pointsW << ")" << endl;
    for (int x =  1; x < 33; x++){
        //we search for pieces that are innactive and are not empty pieces.
        if (!isEmptyPiece(board[x]) && !board[x]->isActive && !board[x]->isWhite){
            pointsB += board[x]->points;
            cout << GREEN << board[x]->display << " " << RESET;
        }
    }
    cout << "(" << pointsB << ")" << endl;
    cout << (isTurnWhite?  RED : GREEN) << '*' << RESET <<" +-----------------------+" << endl;
    for (int i = 0; i < 8; i++)
    {

        cout << 8 - i << " |";
        for (int j = 0; j < 8; j++)
        {
            
            //7-i to properly display y coordinate
            // here we select the first of two chars that represents each cell.
            // * for selected piece
            // + for cells that the selected piece can go
            // selectedPiece == -1 when theres no piece selected
            if (selectedPiece != -1 && moves[j][7 - i]>0)
                cout << "+";
            else if (selectedPiece != -1 && id_board[j][7 - i] == selectedPiece)
            {
                cout << "*";
            }
            else
                cout << " ";

            //7-i to properly display y coordinate
            Piece *p = getPieceAt(j,7 - i);
            cout << ((p->isWhite) ? RED : GREEN) << (p->display) << RESET;

            cout << "|";
        }
        cout << endl;
    }
    cout << "  +-----------------------+" << endl;
    cout << "   1  2  3  4  5  6  7  8" << endl;
    if (selectedPiece != -1)
        delete moves;
}




bool GameManager::movePiece(Piece *piece, int x, int y)
{

    //get possible moves
    int **moves = piece->Update(this, id_board);
    
    //firstly the move must be possible due to the behaviour of the piece, secondly the p
    if (moves[x][y] >=1)
    {
        //get id of the piece we want to move;
        int id = id_board[piece->x][piece->y];

        Piece *p = getPieceAt(x,y);
        if (!isEmptyPiece(p)){
            p->disactivate();
        }

        //write that id to the target chequer.
        id_board[x][y] = id;


        int prevX = piece->x;
        int prevY = piece->y;

        //update values
        piece->x = x;
        piece->y = y;

        //the chequer we have moved from is now empty chequer
        id_board[prevX][prevY] = 0;

        //we successfully made move so next player has to select something.
        selectedPiece = -1;

        for (int i = 0; i < 8; i++)
            delete moves[i];
        delete moves;


        //updateAttackBoards();
        return true;
    }

    for (int i = 0; i < 8; i++)
        delete moves[i];
    delete moves;

    return false;
}

//Pawn should invoke this function when reaches opposite edge of the board. 
void proceed_promotion(Pawn *p){

}


void GameManager::updateAttackBoards()
{

    attackBoardWhite = getArray(8);
    attackBoardBlack = getArray(8);

    for (int i = 0; i < 33; i++)
    {
        //skip empty and innactive fields.
        if (isEmptyPiece(board[i]) || !board[i]->isActive)
            continue;

        int **moves = board[i]->Update(this, id_board);

        if (board[i]->isWhite)

            mergeAttackBoards(attackBoardWhite, moves);

        else

            mergeAttackBoards(attackBoardBlack, moves);

        for (int j = 0; j < 8; j++)
        {
            delete moves[j];
        }
        delete moves;
    }
}

void GameManager::generatePiecePositions()
{
    for (int i = 0; i < 33; i++)
    {
        if(isEmptyPiece(board[i]))
            continue;
        id_board[board[i]->x][board[i]->y] = i;
    }
}

void GameManager::resetBoard()
{
    // add pieces when implemented.
    board[1] = new Pawn(0,1,false);
    board[2] = new Pawn(1,1,false);
    board[3] = new Pawn(2,1,false);
    board[4] = new Pawn(3,1,false);
    board[5] = new Pawn(4,1,false);
    board[6] = new Pawn(5,1,false);
    board[7] = new Pawn(6,1,false);
    board[8] = new Pawn(7,1,false);

    board[9] = new Rook(0,0, false);
    board[10] = new Rook(7,0,false);

    board[11] = new Knight(1,0, false);
    board[12] = new Knight(6,0, false);

    board[13] = new Bishop(2,0, false);
    board[14] = new Bishop(5,0, false);

    board[15] = new King(4,0, false);
    board[16] = new Queen(3,0,false);


    //SECOND COLOR:
    board[17] = new Pawn(0,6,true);
    board[18] = new Pawn(1,6,true);
    board[19] = new Pawn(2,6,true);
    board[20] = new Pawn(3,6,true);
    board[21] = new Pawn(4,6,true);
    board[22] = new Pawn(5,6,true);
    board[23] = new Pawn(6,6,true);
    board[24] = new Pawn(7,6,true);

    board[25] = new Rook(0,7, true);
    board[26] = new Rook(7,7,true);

    board[27] = new Knight(1,7, true);
    board[28] = new Knight(6,7, true);

    board[29] = new Bishop(2,7, true);
    board[30] = new Bishop(5,7, true);

    board[31] = new King(4,7, true);
    board[32] = new Queen(3,7,true);

    //pionek ostatni musi byc z numerem 1 xd

    //procced.
    generatePiecePositions();
    updateAttackBoards();
}

GameManager::GameManager()
{
    isTurnWhite = false;
    selectedPiece = -1;
    id_board = getArray(8);
    attackBoardBlack = getArray(8);
    attackBoardWhite = getArray(8);

    board = new Piece *[33];
    for (int i = 0; i < 33; i++)
    {
        board[i] = new Piece();
    }
}

GameManager::~GameManager()
{
    for (int i = 0; i < 33; ++i)
    {
        delete board[i];
    }
    delete[] board;

    for (int i = 0; i < 8; ++i)
    {
        delete[] id_board[i];
        delete[] attackBoardBlack[i];
        delete[] attackBoardWhite[i];
    }
    delete[] id_board;
    delete[] attackBoardBlack;
    delete[] attackBoardWhite;
}

#include <iostream>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define COLORS  true
#define BLUE    "\033[34m"

class Piece;

class GameManager{
    
    public:
    //two dim array that holds id of pieces that stand on each chequer. 0 represent empty chequer.
    int** id_board;

    //intensity of attack on each chequer.
    int** attackBoardWhite;

    //intensity of attack on each chequer.
    int** attackBoardBlack;

    //list of pieces on the board. id_board can provide indexes when given coordinates of the piece.
    Piece** board;

    //index of the selected piece. -1 if none is selected.
    int selectedPiece;

    //Whos playing
    bool isTurnWhite;

    

    GameManager();
    ~GameManager();

    //Restores default set.
    void resetBoard();

    //Prints board on the screen.
    void printBoard();

    //Used in the main game loop.
    void proceed_turn();

    Piece* getPieceAt(int x, int y);

    private:
    bool isEmptyPiece(Piece *p); 
    void pawnPromo(Piece *p);
    bool movePiece(Piece *piece, int x, int y);
    void updateAttackBoards(); //not working yet
    void generatePiecePositions();

};


class GameManager;

class Piece{

    public:

        //The x coordinate
        int x;
        //The y coordinate
        int y;

        //Team that the piece belongs to.
        //WHITE = RED
        bool isWhite;

        //character used to display piece.
        char display;

        //whether piece is still in-game.
        bool isActive;

        //amount of points player gets after taking the piece.
        int points;

        //Empty chequers are represented by " ".
        Piece();

        //Constructor for regular (not-empty ) pieces.
        Piece(int x_, int y_, bool isWhite_);

        //Vital part of each piece. 
        //Given representation of the state of the board spits the chequers that the piece can go to.    
        virtual int** Update(GameManager *gm,  int **board){};

        //disactivates the piece and moves is out of board.
        void disactivate();
};

class Queen: public Piece{
    public:
    Queen(int x_, int y_, bool white);
	int** Update(GameManager *gm, int **board);
};

class Pawn: public Piece{
    public:
    Pawn(int x, int y, bool isWhite);
    ~Pawn();
    int** Update(GameManager *gm, int **board);
};

class Rook: public Piece{
	public:
		Rook(int x, int y, bool isWhite);
		~Rook();
		int** Update(GameManager *gm, int **board);
};

class King : public Piece
{
public:
    King(int x, int y, bool isWhite);

    ~King();

    int **Update(GameManager *gm, int **board);
};

class Bishop : public Piece{
    public:
    Bishop(int x, int y, bool isWhite);
    int **Update(GameManager *gm, int **board);
};

class Knight : public Piece{
    public:
    Knight(int x, int y, bool isWhite);
    int **Update(GameManager *gm, int **board);
};

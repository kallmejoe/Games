


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#define gridtype vector<vector<gridPosition>>
#define playerstype vector<Player *>
using namespace std;

enum gridPosition
{
    EMPTY,
    YELLOW,
    RED
};

void printLettersofenum(gridtype grid, int c, int r)
{
    switch (grid[r][c])
    {
    case RED:
        cout << "R";
        break;
    case YELLOW:
        cout << "Y";
    default:
        cout << "E";
        break;
    }
};

bool winnerhelper(gridtype matrix, int column, int rows, gridPosition piece)
{
    int count = 0;

    // check 4 vertically
    for (int i = 0; i < rows; i++)
    {
        if (matrix[i][column] == piece)
        {
            count++;
        }
        else
        {
            count = 0;
        }
    }

    // check 4 horizontal
    for (int i = 0; i < column; i++)
    {
        if (matrix[rows][i])
        {
            count++;
        }
        else
        {
            count = 0;
        }
    }

    // check diagonal
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (matrix[i][j])
            {
                count++;
            }
            else
            {
                count = 0;
            }
        }
    }
}

class Grid
{
private:
    int columns;
    int rows;
    vector<vector<gridPosition>> matrix;

public:
    Grid(int cols, int r)
    {
        this->columns = cols;
        this->rows = r;
        init_grid();
    }

    void init_grid()
    {
        matrix.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            matrix[i].resize(columns);
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = EMPTY;
            }
        }
    };

    int placePiece(int col, gridPosition piece)
    {
        if (col < 1 || col > this->columns)
        {
            throw "Invalid Column";
        }
        if (piece == gridPosition::EMPTY)
        {
            throw "Invalid Piece";
        }

        for (int r = this->rows; r >= 0; r--)
        {
            if (this->matrix[r][col] == gridPosition::EMPTY)
            {
                this->matrix[r][col] == piece;
                return r;
            }
        }
    }

    void printBoard()
    {
        system("clear");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; i < columns; j++)
            {
                printLettersofenum(matrix, i, j);
                cout << " ";
            }
            cout << endl;
        }
    }

    gridtype getGrid()
    {
        return this->matrix;
    }
    int getColumn()
    {
        return this->columns;
    }

    bool isAWinner(int connectN, int row, int column, gridPosition piece)
    {
        int count = 0;

        // check 4 vertically
        for (int i = 0; i < rows; i++)
        {
            if (matrix[i][column] == piece)
            {
                count++;
            }
            else
            {
                count = 0;
            }
        }
    }
};

class Player
{
private:
    string name;
    gridPosition piece;
    int score;

public:
    Player(string name, gridPosition piece, int score = 0)
    {
        this->name = name;
        this->piece = piece;
        this->score = score;
    }

    string getName()
    {
        return this->name;
    }

    gridPosition getPieceColor()
    {
        return this->piece;
    }

    int getScore()
    {
        return this->score;
    }

    void incrementScore()
    {
        this->score += 1;
    }
};

class Game
{
    Grid *grid;
    int connectN;
    playerstype players;
    int targetScore;
    public:

    Game(Grid *grid, int targetScore, int connectN)
    {
        this->grid = grid;
        this->targetScore = targetScore;
        this->connectN = connectN;

        this->players = playerstype{
            new Player("player 1", RED),
            new Player("Player 2", YELLOW)};
    };

    pair<int, int> playerMove(Player *player)
    {
        grid->printBoard();
        cout << player->getName() << "turn" << endl;
        int colscnt = grid->getColumn();
        cout << "Enter a Column number" << endl;
        int chosencol;
        cin >> chosencol;
        int chosenRow = grid->placePiece(chosencol, player->getPieceColor());
        return {chosencol, chosenRow};
    }
    Player *playerRound()
    {
        while (true)
        {

            for (Player *player : this->players)
            {
                pair<int, int> position = playerMove(player);
                int col = position.first;
                int row = position.second;
                gridPosition pieceColor = player->getPieceColor();
                if (this->grid->isAWinner(connectN, row, col, pieceColor))
                {
                    player->incrementScore();
                    return player;
                }
            }
        }
    }

    void playTheGame()
    {
        int gameScore = 0;
        Player *winner = nullptr;
        while (gameScore < targetScore)
        {
            winner = playerRound();
            cout<<winner->getName()<<"won the round"<<endl;
            this->grid->init_grid();        
        }
        cout<<winner->getName()<<"Won the Game"<<endl;
    }
};

int main()
{
    
    Grid* grid = new Grid(6,7);
    Game* game = new Game(grid,4,10);
    game->playTheGame();

    system("pause");
    return 0;
}

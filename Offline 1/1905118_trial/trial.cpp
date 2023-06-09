#include <bits/stdc++.h>
using namespace std;

// parMove values :-> up : 1, down : 2, right : 3, left : 4

class Board
{

private:
    vector<vector<int>> board;
    int gridSize, gVal, hVal, fVal, hFlag, parMove;
    Board *parent;

public:
    Board(int gridSize, vector<vector<int>> board, Board *parent, int hFlag, int parMove)
    {
        this->gridSize = gridSize;
        this->board = board;
        this->parent = parent;
        this->hFlag = hFlag;
        this->parMove = parMove;

        if (this->parent == nullptr)
        {
            this->gVal = 0;
        }
        else
        {
            this->gVal = this->parent->gVal + 1;
        }

        if (hFlag == 0)
        {
            this->hVal = this->getHammingDistance();
        }
        else if (hFlag == 1)
        {
            this->hVal = this->getManhattanDistance();
        }

        this->fVal = this->gVal + this->hVal;
    }

    vector<vector<int>> getBoard() {
        return this->board;
    }

    Board* getParent() {
        return this->parent;
    }

    int getFVal() {
        return this->fVal;
    }

    int getHammingDistance()
    {
        int hammingDistance = 0;
        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                if (this->board[i][j] != 0)
                {
                    if (this->board[i][j] != ((this->gridSize * i + j) + 1))
                    {
                        hammingDistance++;
                    }
                }
            }
        }
        return hammingDistance;
    }

    int getManhattanDistance()
    {
        int manhattanDistance = 0;
        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                if (this->board[i][j] != 0)
                {
                    int goal_i = (this->board[i][j] - 1) / this->gridSize;
                    int goal_j = (this->board[i][j] - 1) % this->gridSize;
                    manhattanDistance += (abs(i - goal_i) + abs(j - goal_j));
                }
            }
        }
        return manhattanDistance;
    }

    int getBlankTilePos()
    {
        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                if (this->board[i][j] == 0)
                {
                    return (this->gridSize * i + j);
                }
            }
        }
        return -1;
    }

    int getInversionCount()
    {
        set<int> s;
        int invCnt = 0;
        for (int i = this->gridSize - 1; i >= 0; i--)
        {
            for (int j = this->gridSize - 1; j >= 0; j--)
            {
                if (this->board[i][j] != 0)
                {
                    s.insert(this->board[i][j]);
                    auto it = s.lower_bound(this->board[i][j]);
                    invCnt += distance(s.begin(), it);
                }
            }
        }
        return invCnt;
    }

    bool canUp()
    {
        if (this->parMove == 2)
        {
            return false;
        }
        else if ((this->getBlankTilePos() / this->gridSize) <= 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool canDown()
    {
        if (this->parMove == 1)
        {
            return false;
        }
        else if ((this->getBlankTilePos() / this->gridSize) >= this->gridSize - 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool canRight()
    {
        if (this->parMove == 4)
        {
            return false;
        }
        else if ((this->getBlankTilePos() % this->gridSize) >= this->gridSize - 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool canLeft()
    {
        if (this->parMove == 3)
        {
            return false;
        }
        else if ((this->getBlankTilePos() % this->gridSize) <= 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void printBoard()
    {
        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                cout << this->board[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }

    Board *getUpNeighbour()
    {
        vector<vector<int>> temp = this->board;
        int blank_i = this->getBlankTilePos() / this->gridSize;
        int blank_j = this->getBlankTilePos() % this->gridSize;
        swap(temp[blank_i][blank_j], temp[blank_i - 1][blank_j]);
        return (new Board(this->gridSize, temp, this, this->hFlag, 1));
    }

    Board *getDownNeighbour()
    {
        vector<vector<int>> temp = this->board;
        int blank_i = this->getBlankTilePos() / this->gridSize;
        int blank_j = this->getBlankTilePos() % this->gridSize;
        swap(temp[blank_i][blank_j], temp[blank_i + 1][blank_j]);
        return (new Board(this->gridSize, temp, this, this->hFlag, 2));
    }

    Board *getRightNeighbour()
    {
        vector<vector<int>> temp = this->board;
        int blank_i = this->getBlankTilePos() / this->gridSize;
        int blank_j = this->getBlankTilePos() % this->gridSize;
        swap(temp[blank_i][blank_j], temp[blank_i][blank_j + 1]);
        return (new Board(this->gridSize, temp, this, this->hFlag, 3));
    }

    Board *getLeftNeighbour()
    {
        vector<vector<int>> temp = this->board;
        int blank_i = this->getBlankTilePos() / this->gridSize;
        int blank_j = this->getBlankTilePos() % this->gridSize;
        swap(temp[blank_i][blank_j - 1], temp[blank_i][blank_j]);
        return (new Board(this->gridSize, temp, this, this->hFlag, 4));
    }
};

class Compare
{
public:
    bool operator() (Board *a, Board *b) {
        return a->getFVal() > b->getFVal();
    }
};

class AStar
{

private:
    Board *initialBoard;
    vector<vector<int>> goalBoard;
    int gridSize;
    set<Board *> boards;
    priority_queue<Board*, vector<Board*>, Compare> pq;

    void makeGoalBoard()
    {
        this->goalBoard.resize(this->gridSize, vector<int>(this->gridSize));
        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                this->goalBoard[i][j] = this->gridSize * i + j + 1;
            }
        }
        this->goalBoard[this->gridSize - 1][this->gridSize - 1] = 0;
    }

    void freeUpMemory()
    {
        for (Board *x : this->boards)
        {
            delete x;
        }
    }

    void printMoves(Board* top) {
        if(top->getParent() != nullptr) {
            this->printMoves(top->getParent());
        }
        top->printBoard();
    }

public:
    AStar(int gridSize, vector<vector<int>> initialBoard, int hFlag)
    {
        this->gridSize = gridSize;
        this->initialBoard = new Board(gridSize, initialBoard, nullptr, hFlag, -1);
        this->boards.insert(this->initialBoard);
        this->makeGoalBoard();
        this->pq.push(this->initialBoard);
    }

    bool isSolvable()
    {
        int invCnt = this->initialBoard->getInversionCount();
        if (this->gridSize & 1)
        {
            return !(invCnt & 1);
        }
        else
        {
            int blank_row = this->initialBoard->getBlankTilePos() / this->gridSize;
            return (blank_row & 1) ^ (invCnt & 1);
        }
    }

    void search()
    {
        while(!this->pq.empty()) {
            Board *top = this->pq.top();
            this->pq.pop();
            if(top->getBoard() == this->goalBoard) {
                cout << "Minimum number of moves = " << top->getFVal() << "\n\n";
                this->printMoves(top);
                this->freeUpMemory();
                break;
            }
            else {
                Board *temp;
                if(top->canUp()) {
                    temp = top->getUpNeighbour();
                    this->boards.insert(temp);
                    this->pq.push(temp);
                }
                if(top->canDown()) {
                    temp = top->getDownNeighbour();
                    this->boards.insert(temp);
                    this->pq.push(temp);
                }
                if(top->canRight()) {
                    temp = top->getRightNeighbour();
                    this->boards.insert(temp);
                    this->pq.push(temp);
                }
                if(top->canLeft()) {
                    temp = top->getLeftNeighbour();
                    this->boards.insert(temp);
                    this->pq.push(temp);
                }
            }
        }
    }   
};

int main()
{

    freopen("in.txt", "r", stdin);

    int n;
    string s;

    getline(cin, s);

    n = stoi(s);

    vector<vector<int>> v(n);

    for (int i = 0; i < n; i++)
    {
        getline(cin, s);
        istringstream ss(s);
        while (ss >> s)
        {
            v[i].push_back(stoi(s));
        }
    }

    AStar graph(n, v, 1);
    
    if(graph.isSolvable()) {
        graph.search();
    }
    else {
        cout << "Unsolvable\n";
    }

    return 0;
}
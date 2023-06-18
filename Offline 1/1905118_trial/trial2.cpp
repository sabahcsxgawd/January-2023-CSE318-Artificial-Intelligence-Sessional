#include <bits/stdc++.h>
using namespace std;


class Board {

private:
    string moves;
    int gVal, hVal, gridSize;

public:
    Board(const string& moves, int gVal, int hVal, int gridSize) {
        this->moves = moves;
        this->gVal = gVal;
        this->hVal = hVal;
        this->gridSize = gridSize;
    }

    const string& getMoves() {
        return this->moves;
    }

    int getGVal() {
        return this->gVal;
    }

    int getHVal() {
        return this->hVal;
    }

    bool canUp(char parMove, int blank_i) {
        if(parMove == 'D') {
            return false;
        }
        else if(blank_i <= 0) {
            return false;
        }
        else {
            return true;
        }
    }

    bool canDown(char parMove, int blank_i) {
        if(parMove == 'U') {
            return false;
        }
        else if(blank_i >= this->gridSize - 1) {
            return false;
        }
        else {
            return true;
        }
    }

    bool canRight(char parMove, int blank_j) {
        if(parMove == 'L') {
            return false;
        }
        else if(blank_j >= this->gridSize - 1) {
            return false;
        }
        else {
            return true;
        }
    }

    bool canLeft(char parMove, int blank_j) {
        if(parMove == 'R') {
            return false;
        }
        else if(blank_j <= 0) {
            return false;
        }
        else {
            return true;
        }
    }

    void setHVal(int hVal) {
        this->hVal = hVal;
    }
};

class Compare
{
public:
    bool operator() (Board a, Board b) {
        return ((a.getGVal() + a.getHVal()) > (b.getGVal() + b.getHVal()));
    }
};

class AStar {

private:
    vector<vector<int>> initialBoard, goalBoard, tempBoard;
    int gridSize, initial_blank_i, initial_blank_j, hFlag;
    const pair<int, int> directions[4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}; // UP, DOWN, RIGHT, LEFT
    priority_queue<Board, vector<Board>, Compare> pq;

    int getInversionCount() {
        set<int> s;
        int invCnt = 0;
        for (int i = this->gridSize - 1; i >= 0; i--)
        {
            for (int j = this->gridSize - 1; j >= 0; j--)
            {
                if (this->initialBoard[i][j] != 0)
                {
                    s.insert(this->initialBoard[i][j]);
                    auto it = s.lower_bound(this->initialBoard[i][j]);
                    invCnt += distance(s.begin(), it);
                }
            }
        }
        return invCnt;
    }

    int getNewHVal(int oldHVal, int cur_blank_i, int cur_blank_j, const pair<int, int> &direction) {
        // manhattan
        if(this->hFlag) {
            return this->getNewManhattan(oldHVal, cur_blank_i, cur_blank_j, direction);
        }

        // hamming
        else {
            return this->getNewHamming(oldHVal, cur_blank_i, cur_blank_j, direction);
        }
    }

    int getNewHamming(int oldHVal, int cur_blank_i, int cur_blank_j, const pair<int, int> &direction) {
        int oldTileVal = this->tempBoard[cur_blank_i + direction.first][cur_blank_j + direction.second];
        int goalTileVal1 = this->goalBoard[cur_blank_i + direction.first][cur_blank_j + direction.second];
        int goalTileVal2 = this->goalBoard[cur_blank_i][cur_blank_j];

        return (oldHVal - (oldTileVal != goalTileVal1) + (oldTileVal != goalTileVal2));
    }

    int getNewManhattan(int oldHVal, int cur_blank_i, int cur_blank_j, const pair<int, int> &direction) {
        int old_i = cur_blank_i + direction.first;
        int old_j = cur_blank_j + direction.second;
        int actual_i = (this->tempBoard[old_i][old_j] - 1) / this->gridSize;
        int actual_j = (this->tempBoard[old_i][old_j] - 1) % this->gridSize;

        return (oldHVal - (abs(actual_i - old_i) + abs(actual_j - old_j)) + (abs(actual_i - cur_blank_i) + abs(actual_j - cur_blank_j)));
    }

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
    
    int getInitialHammingDistance() {
        int hammingDistance = 0;
        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                if (this->initialBoard[i][j] != 0)
                {
                    if (this->initialBoard[i][j] != ((this->gridSize * i + j) + 1))
                    {
                        hammingDistance++;
                    }
                }
            }
        }
        return hammingDistance;
    }

    int getInitialManhattanDistance() {
        int manhattanDistance = 0;
        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                if (this->initialBoard[i][j] != 0)
                {
                    int goal_i = (this->initialBoard[i][j] - 1) / this->gridSize;
                    int goal_j = (this->initialBoard[i][j] - 1) % this->gridSize;
                    manhattanDistance += (abs(i - goal_i) + abs(j - goal_j));
                }
            }
        }
        return manhattanDistance;
    }

public:
    AStar(const vector<vector<int>>& initialBoard, int gridSize, int initial_blank_i, int initial_blank_j, int hFlag) {
        this->initialBoard = initialBoard;
        this->gridSize = gridSize;
        this->initial_blank_i = initial_blank_i;
        this->initial_blank_j = initial_blank_j;
        this->hFlag = hFlag;
        this->makeGoalBoard();
        Board board("", 0, 0, gridSize);
        if(this->hFlag) {
            board.setHVal(this->getInitialManhattanDistance());
        }
        else {
            board.setHVal(this->getInitialHammingDistance());
        }      
        this->pq.push(board);
    }

    bool isSolvable() {
        int invCnt = this->getInversionCount();
        if (this->gridSize & 1)
        {
            return !(invCnt & 1);
        }
        else
        {
            return (this->initial_blank_i & 1) ^ (invCnt & 1);
        }
    }

    void search() {
        while(!this->pq.empty()) {
            Board top = this->pq.top();
            int oldHVal = top.getHVal();
            int oldGVal = top.getGVal();
            if(oldHVal == 0) {
                cout << "Minimum number of moves = " << oldGVal << "\n\n";
                break;
            }
            else {
                this->pq.pop();
                this->tempBoard = this->initialBoard;
                int temp_blank_i = this->initial_blank_i, temp_blank_j = this->initial_blank_j;
                string moves = top.getMoves();                
                for(char c : moves) {
                    if(c == 'U') {
                        swap(tempBoard[temp_blank_i][temp_blank_j], tempBoard[temp_blank_i - 1][temp_blank_j]);
                        temp_blank_i -= 1;
                    }
                    else if(c == 'D'){
                        swap(tempBoard[temp_blank_i][temp_blank_j], tempBoard[temp_blank_i + 1][temp_blank_j]);
                        temp_blank_i += 1;
                    }
                    else if(c == 'R') {
                        swap(tempBoard[temp_blank_i][temp_blank_j], tempBoard[temp_blank_i][temp_blank_j + 1]);
                        temp_blank_j += 1;
                    }
                    else if(c == 'L') {
                        swap(tempBoard[temp_blank_i][temp_blank_j], tempBoard[temp_blank_i][temp_blank_j - 1]);
                        temp_blank_j -= 1;
                    }
                }
                int newHVal;
                if(top.canUp(moves.back(), temp_blank_i)) {
                    newHVal = this->getNewHVal(oldHVal, temp_blank_i, temp_blank_j, this->directions[0]);
                    this->pq.push(Board(moves + 'U', oldGVal + 1, newHVal, gridSize));
                }
                if(top.canDown(moves.back(), temp_blank_i)) {
                    newHVal = this->getNewHVal(oldHVal, temp_blank_i, temp_blank_j, this->directions[1]);
                    this->pq.push(Board(moves + 'D', oldGVal + 1, newHVal, gridSize));
                }
                if(top.canRight(moves.back(), temp_blank_j)) {
                    newHVal = this->getNewHVal(oldHVal, temp_blank_i, temp_blank_j, this->directions[2]);
                    this->pq.push(Board(moves + 'R', oldGVal + 1, newHVal, gridSize));
                }
                if(top.canLeft(moves.back(), temp_blank_j)) {
                    newHVal = this->getNewHVal(oldHVal, temp_blank_i, temp_blank_j, this->directions[3]);
                    this->pq.push(Board(moves + 'L', oldGVal + 1, newHVal, gridSize));
                }
            }
        }
    }

};

int main(int argc, char *argv[])
{

    freopen(argv[1], "r", stdin);
    // freopen(argv[2], "w", stdout);

    int gridSize, blank_i, blank_j;

    cin >> gridSize;

    vector<vector<int>> v(gridSize, vector<int>(gridSize));

    for (int i = 0; i < gridSize; i++)
    {
       for(int j = 0; j < gridSize; j++) {
            cin >> v[i][j];
            if(v[i][j] == 0) {
                blank_i = i;
                blank_j = j;
            }
       }
    }

    AStar graph(v, gridSize, blank_i, blank_j, 1);

    if(!graph.isSolvable()) {
        cout << "Unsolvable puzzle\n";
    }

    else {
        // cout << "Solvable puzzle\n";
        graph.search();
    }

    return 0;
}
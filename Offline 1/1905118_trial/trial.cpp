#include <bits/stdc++.h>
using namespace std;


class Board {

private:
    vector<vector<int>> board;
    int gridSize, gVal, hVal, fVal, parMove;
    shared_ptr<Board> parent;


public:
    Board(int gridSize, vector<vector<int>> board, shared_ptr<Board> parent, int hFlag) {
        this->gridSize = gridSize;
        this->board = board;
        this->parent = parent;

        if(this->parent == nullptr) {
            this->gVal = 0;
            this->parMove = -1;
        }
        else {
            this->gVal = parent->gVal + 1;
        }

        if(hFlag == 0) {
            this->hVal = this->getHammingDistance();
        }
        else if(hFlag == 1) {
            this->hVal = this->getManhattanDistance();
        }
        
        this->fVal = this->gVal + this->hVal;
    }

    int getGVal() {
        return this->gVal;
    }

    int getHammingDistance() {
        int hammingDistance = 0;
        for(int i = 0; i < this->gridSize; i++) {
            for(int j = 0; j < this->gridSize; j++) {
                if(this->board[i][j] != 0) {
                    if(this->board[i][j] != (this->gridSize * i + j) + 1) {
                        hammingDistance++;
                    }
                }
            }
        }
        return hammingDistance;
    }

    int getManhattanDistance() {
        int manhattanDistance = 0;
        for(int i = 0; i < this->gridSize; i++) {
            for(int j = 0; j < this->gridSize; j++) {
                if(this->board[i][j] != 0) {
                    int goal_i = (this->board[i][j] - 1) / this->gridSize;
                    int goal_j = (this->board[i][j] - 1) % this->gridSize;
                    manhattanDistance += (abs(i - goal_i) + abs(j - goal_j));
                }
            }
        }
        return manhattanDistance;
    }

    int getBlankTilePos() {
        for(int i = 0; i < this->gridSize; i++) {
            for(int j = 0; j < this->gridSize; j++) {
                if(this->board[i][j] == 0) {
                    return (this->gridSize * i + j);
                }
            }
        }
    }

    int getInversionCount() {

    }

    bool canUp() {

    }

    bool canDown() {
        
    }

    bool canRight() {
        
    }

    bool canLeft() {
        
    }

    void setParMove(int parMove) {
        this->parMove = parMove;
    }

    void printBoard() {

    }

};



int main() {

    freopen("in.txt", "r", stdin);

    int n;
    string s;

    getline(cin, s);

    n = stoi(s);

    vector<vector<int>> v(n);

    for(int i = 0; i < n; i++) {
        getline(cin, s);
        istringstream ss(s);
        while(ss >> s) {
            v[i].push_back(stoi(s));
        }
    }

    
    return 0;
}
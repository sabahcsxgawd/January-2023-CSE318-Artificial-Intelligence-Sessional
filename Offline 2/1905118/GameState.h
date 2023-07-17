#pragma once

class GameState {

private:
    bool whichPlayer; // Two Players denoted by 0 and 1
    int state[14];
    int selectedBinToReachThisState;
    GameState* parent;

public:
    GameState() = delete;

    GameState(const GameState &) = delete;

    GameState(bool whichPlayer, int state[], int selectedBinToReachThisState, GameState* parent) {
        this->whichPlayer = whichPlayer;
        for(int i = 0; i < 14; i++) {
            this->state[i] = state[i];
        }
        this->parent = parent;
        this->selectedBinToReachThisState = selectedBinToReachThisState;
    }

    static GameState* getInitialState(bool whichPlayer) {
        int initialState[14];

        for(int i = 0; i < 14; i++) {
            initialState[i] = 4;
        }

        initialState[6] = initialState[13] = 0;

        // cin >> initialState[13];
        // cin >> initialState[12];
        // cin >> initialState[11];
        // cin >> initialState[10];
        // cin >> initialState[9];
        // cin >> initialState[8];
        // cin >> initialState[7];
        // cin >> initialState[6];
        // cin >> initialState[0];
        // cin >> initialState[1];
        // cin >> initialState[2];
        // cin >> initialState[3];
        // cin >> initialState[4];
        // cin >> initialState[5];
    
        return new GameState(whichPlayer, initialState, -1, nullptr);
    }

    void printState() {
        cout << right;
        for(int i = 12; i > 6; i--) {
            cout << setw(4) << this->state[i];
        }
        cout << '\n';
        
        cout << this->state[13];
        for(int i = 0; i < 6; i++) {
            cout << setw(4) << "";
        }
        cout << setw(2) << this->state[6];
        cout << '\n';
        
        for(int i = 0; i < 6; i++) {
            cout << setw(4) << this->state[i];
        }
        cout << '\n';
    }

    GameState* changeState(int bin) {
        GameState *temp = this->getNextState(bin);
        temp->parent = nullptr;
        return temp;
    }

    void setParent(GameState *parent) {
        this->parent = parent;
    }

    bool getWhichPlayer() {
        return this->whichPlayer;
    }

    int getSelectedBin() {
        return this->selectedBinToReachThisState;
    }

    int getStones(int bin) {
        return this->state[bin];
    }

    bool isFinalState() {
        bool isEmpty0 = true;
        bool isEmpty1 = true;

        for(int i = 0; i < 6; i++) {
            if(this->state[i] > 0) {
                isEmpty0 = false;
                break;
            }
        }

        for(int i = 7; i < 13; i++) {
            if(this->state[i] > 0) {
                isEmpty1 = false;
                break;
            }
        }

        return isEmpty0 || isEmpty1;
    }

    int8_t getStorageStoneDifference(bool whichPlayer) {
        if(whichPlayer) {
            return (this->state[13] - this->state[6]);
        } else {
            return (this->state[6] - this->state[13]);
        }
    }

    int8_t getTotalBinStoneDifference(bool whichPlayer) {
        int8_t diff = 0;
        
        for(int i = 0; i < 6; i++) {
            diff += (this->state[i] - this->state[i + 7]);
        }

        if(whichPlayer) {
            return -diff;
        } else {
            return diff;   
        }        
    }

    int8_t getAdditionalMovesEarned(bool whichPlayer) {
        if(this->parent && this->parent->whichPlayer == this->whichPlayer) {
            if(this->whichPlayer == whichPlayer) {
                return 1;
            }
            else { // adverse effect
                return -1;
            }
        }
        else {
            return 0;
        }
    }

    int8_t getStonesCaptured(bool whichPlayer) {        
        if(this->parent) {
            int8_t stonesCaptured0 = this->state[0] - this->parent->state[0];
            int8_t stonesCaptured1 = this->state[13] - this->parent->state[13];

            if(this->parent->whichPlayer == whichPlayer) {
                if(whichPlayer) {
                    return stonesCaptured1;
                }
                else {
                    return stonesCaptured0;
                }
            }
            else { // adverse effect
                if(whichPlayer) {
                    return -stonesCaptured0;
                }
                else {
                    return -stonesCaptured1;
                }
            }
        }
        else {
            return 0;
        }
    }

    GameState* getNextState(int bin) {        
        int tempBin = bin;
        int stones = this->state[bin];
        bool nextWhichPlayer = this->whichPlayer ^ 1;
        int nextState[14];
        for(int i = 0; i < 14; i++) {
            nextState[i] = this->state[i];
        }

        nextState[bin] = 0;            

        while(stones) {
            bin = (bin + 1) % 14;
            stones--;
            if((this->whichPlayer && bin == 6) || (!this->whichPlayer && bin == 13)) {
                bin = (bin + 1) % 14;
            }
            nextState[bin]++;
        }

        // set proper player turn after gaining extra move
        if(bin == 6 && !this->whichPlayer) {
            nextWhichPlayer = 0;
        }
        else if(bin == 13 && this->whichPlayer) {
            nextWhichPlayer = 1;
        }

        // get the empty pit advantage
        if((!whichPlayer) && (0 <= bin) && (bin < 6) && (nextState[bin] == 1) && (nextState[12 - bin])) {
            nextState[6] += 1 + nextState[12 - bin];
            nextState[bin] = nextState[12 - bin] = 0;
        }
        else if((whichPlayer) && (7 <= bin) && (bin < 13) && (nextState[bin] == 1) && (nextState[12 - bin])) {
             nextState[13] += 1 + nextState[12 - bin];
            nextState[bin] = nextState[12 - bin] = 0;
        }

        if(this->isFinalState()) {
            cout << "final\n";
            this->finalStoneCollection();
        }

        return new GameState(nextWhichPlayer, nextState, tempBin, this);        
    }

    void finalStoneCollection() {
        for(int i = 0; i < 6; i++) {
            this->state[6] += this->state[i];            
            this->state[i] = 0;
            this->state[13] += this->state[i + 7];
            this->state[i + 7] = 0;
        }
    }

    bool getWinner() { // assuming the state is terminal
        if(this->state[13] > this->state[6]) {
            return 1;
        }
        else if(this->state[13] < this->state[6]) {
            return 0;
        }
        else {
            return 2; // draw
        }
    }

};
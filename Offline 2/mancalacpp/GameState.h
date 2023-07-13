#pragma once

// TODO remove when submitting
// #include <bits/stdc++.h>

class GameState {

private:
    bool whichPlayer; // Two Players denoted by 0 and 1
    uint8_t state[14];
    uint8_t selectedBinToReachThisState;
    GameState* parent;

public:
    GameState() = delete;

    GameState(const GameState &) = delete;

    GameState(bool whichPlayer, uint8_t state[], uint8_t selectedBinToReachThisState, GameState* parent) {
        this->whichPlayer = whichPlayer;
        for(int i = 0; i < 14; i++) {
            this->state[i] = state[i];
        }
        this->parent = parent;
        this->selectedBinToReachThisState = selectedBinToReachThisState;
    }

    bool isFinalState() {
        bool isEmpty0 = true;
        bool isEmpty1 = true;

        for(int i = 0; i < 6; i++) {
            if(this->state[i] > 0) {
                isEmpty0 = false;
            }
        }

        for(int i = 7; i < 13; i++) {
            if(this->state[i] > 0) {
                isEmpty1 = false;
            }
        }

        return isEmpty0 || isEmpty1;
    }

    int8_t getStorageStoneDifference(uint8_t whichPlayer) {
        if(whichPlayer) {
            return (this->state[13] - this->state[6]);
        } else {
            return (this->state[6] - this->state[13]);
        }
    }

    int8_t getTotalBinStoneDifference(uint8_t whichPlayer) {
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

    int8_t getAdditionalMovesEarned(uint8_t whichPlayer) {
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

    int8_t getStonesCaptured(uint8_t whichPlayer) {        
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

    GameState* getNextState(uint8_t bin) {        
        uint8_t tempBin = bin;
        uint8_t stones = this->state[bin];
        uint8_t nextWhichPlayer = this->whichPlayer ^ 1;
        uint8_t nextState[14] = {0};
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

        // get extra move
        if(bin == 6 && !this->whichPlayer) {
            nextWhichPlayer = 0;
        }
        else if(bin == 13 && this->whichPlayer) {
            nextWhichPlayer = 1;
        }

        // get the empty pit advantage
        if(!whichPlayer && 0 <= bin && bin < 6 && nextState[bin] == 1) {
            nextState[6] += 1 + nextState[bin + ((6 - bin) << 1)];
        }
        else if(whichPlayer && 7 <= bin && bin < 14 && nextState[bin] == 1) {
            nextState[13] += 1 + nextState[bin - ((bin - 6) << 1)];
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
        return this->state[13] > this->state[0];
    }

};
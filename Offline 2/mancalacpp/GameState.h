#pragma once

// TODO remove when submitting
#include <bits/stdc++.h>

class GameState {

private:
    bool whichPlayer;
    uint8_t state[14];
    GameState* parent;

public:
    GameState(bool whichPlayer, uint8_t state[], GameState* parent) {
        this->whichPlayer = whichPlayer;
        for(int i = 0; i < 14; i++) {
            this->state[i] = state[i];
        }
        this->parent = parent;
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
            else {
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
            else {
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

};
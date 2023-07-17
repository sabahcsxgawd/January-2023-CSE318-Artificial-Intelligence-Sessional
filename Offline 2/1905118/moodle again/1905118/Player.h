#pragma once

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


class Player {

private:
    bool whichPlayer;
    int maxDepth;
    heuristics heuristic;

public:
    Player() = delete;

    Player(const Player& player) = delete;

    Player(bool whichPlayer, int maxDepth, int heuristicID) {
        this->whichPlayer = whichPlayer;
        this->maxDepth = maxDepth;
        this->heuristic = getHeuristic(heuristicID);
    }

    pair<int, int> minimaxAlphaBetaPruning(GameState *gameState, int depth, int alpha, int beta, bool maxPlayer) {
        if(depth == this->maxDepth || gameState->isFinalState()) {
            return make_pair(this->heuristic(gameState, this->whichPlayer), gameState->getSelectedBin());
        }

        vector<GameState*> childStates;
        
        if(gameState->getWhichPlayer()) {
            for(int i = 7; i < 13; i++) {
                if(gameState->getStones(i)) {
                    childStates.push_back(gameState->getNextState(i));
                }
            }
        }
        else {
            for(int i = 0; i < 6; i++) {
                if(gameState->getStones(i)) {
                    childStates.push_back(gameState->getNextState(i));
                }
            }
        }

        shuffle(childStates.begin(), childStates.end(), rng);

        if(maxPlayer) {
            pair<int, int> maxPair = make_pair(INT_MIN, NULL);
            for(GameState *child : childStates) {
                pair<int, int> temp = minimaxAlphaBetaPruning(child, depth + 1, alpha, beta, (this->whichPlayer == child->getWhichPlayer()));
                if(temp.first > maxPair.first) {
                    maxPair.first = temp.first;
                    maxPair.second = child->getSelectedBin();
                }
                if(temp.first > alpha) {
                    alpha = temp.first;
                }
                if(alpha >= beta) {
                    break;
                }
            }

            for(GameState *child : childStates) {
                delete child;
            }
            
            return maxPair;
        }
        else {
            pair<int, int> minPair = make_pair(INT_MAX, NULL);
            for(GameState *child : childStates) {
                pair<int, int> temp = minimaxAlphaBetaPruning(child, depth + 1, alpha, beta, (this->whichPlayer == child->getWhichPlayer()));
                if(temp.first < minPair.first) {
                    minPair.first = temp.first;
                    minPair.second = child->getSelectedBin();
                }
                if(temp.first < beta) {
                    beta = temp.first;
                }
                if(alpha >= beta) {
                    break;
                }
            }
            
            for(GameState *child : childStates) {
                delete child;
            }
            
            return minPair;
        }
    }
};
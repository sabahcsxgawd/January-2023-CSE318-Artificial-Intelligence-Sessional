#pragma once

typedef int (*heuristics)(GameState *gameState, bool whichPlayer);

// TODO initialize these weights
int W1 = 100, W2 = 100, W3 = 100, W4 = 100;

int heuristic0(GameState *gameState, bool whichPlayer) {
    return gameState->getStorageStoneDifference(whichPlayer);
}

int heuristic1(GameState *gameState, bool whichPlayer) {
    return (W1 * gameState->getStorageStoneDifference(whichPlayer) + W2 * gameState->getTotalBinStoneDifference(whichPlayer));
}

int heuristic2(GameState *gameState, bool whichPlayer) {
    return (W1 * gameState->getStorageStoneDifference(whichPlayer) + W2 * gameState->getTotalBinStoneDifference(whichPlayer) + W3 * gameState->getAdditionalMovesEarned(whichPlayer));
}

int heuristic3(GameState *gameState, bool whichPlayer) {
    return (W1 * gameState->getStorageStoneDifference(whichPlayer) + W2 * gameState->getTotalBinStoneDifference(whichPlayer) + W3 * gameState->getAdditionalMovesEarned(whichPlayer) + W4 * gameState->getStonesCaptured(whichPlayer));
}

heuristics heuristicsArr[]= {
    heuristic0,
    heuristic1,
    heuristic2,
    heuristic3
};

heuristics getHeuristic(int heuristicID) {
    return heuristicsArr[heuristicID];
}
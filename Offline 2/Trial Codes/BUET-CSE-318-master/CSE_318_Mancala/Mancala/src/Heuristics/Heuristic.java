package Heuristics;

import Mancala.State;

public interface Heuristic {
    int evaluateState(State state, int playerNumber);
}

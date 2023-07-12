package Heuristics;

import Mancala.State;

public class Heuristic1 implements Heuristic {

    @Override
    public int evaluateState(State state, int playerNumber) {
       return state.getStorageDiff(playerNumber);
    }
}

package Heuristics;

import Mancala.State;

public class Heuristic2 implements Heuristic {
    private int w1;
    private int w2;

    public Heuristic2(int w1, int w2) {
        this.w1 = w1;
        this.w2 = w2;
    }

    @Override
    public int evaluateState(State state, int playerNumber) {

        return w1*state.getStorageDiff(playerNumber)+w2*state.getBinsDiff(playerNumber);
    }
}

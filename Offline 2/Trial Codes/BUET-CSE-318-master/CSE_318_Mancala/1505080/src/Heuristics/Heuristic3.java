package Heuristics;

import Mancala.State;

public class Heuristic3 implements Heuristic {
    private int w1;
    private int w2;
    private int w3;

    public Heuristic3(int w1, int w2, int w3) {
        this.w1 = w1;
        this.w2 = w2;
        this.w3 = w3;
    }

    @Override
    public int evaluateState(State state, int playerNumber) {
        return w1*state.getStorageDiff(playerNumber)+w2*state.getBinsDiff(playerNumber)+w3*state.extraTurn(playerNumber);
    }
}

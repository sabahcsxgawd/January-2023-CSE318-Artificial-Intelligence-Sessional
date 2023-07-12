package Heuristics;

import Mancala.State;

public class Heuristic5 implements Heuristic{
    private int w1;
    private int w2;
    private int w3;
    private int w4;

    public Heuristic5(int w1, int w2, int w3, int w4) {
        this.w1 = w1;
        this.w2 = w2;
        this.w3 = w3;
        this.w4 = w4;
    }

    @Override
    public int evaluateState(State state, int playerNumber) {
        return w1*state.getStorageDiff(playerNumber)+w2*state.getCloseToStorageDiff(playerNumber)+w3*state.extraTurn(playerNumber)+w4*state.numStoneCaptured(playerNumber);
    }
}

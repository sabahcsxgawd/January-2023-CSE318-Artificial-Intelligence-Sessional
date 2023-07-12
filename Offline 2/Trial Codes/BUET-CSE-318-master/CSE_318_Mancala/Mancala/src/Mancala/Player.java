package Mancala;

import Heuristics.Heuristic;
import javafx.util.Pair;

import java.util.ArrayList;

public class Player{

    public static final int MINUS_INF = -99999999;
    public static final int PLUS_INF = 99999999;

    int playerNumber;
    Heuristic heuristic;

    public Player(int playerNumber, Heuristic heuristic) {
        this.playerNumber = playerNumber;
        this.heuristic = heuristic;


    }

    State giveMove(State currentState){
//        State tempState = minimax(currentState, Main.MINIMAX_SEARCH_DEPTH, true).getKey();

        State tempState = minimaxWithPruning(currentState, Main.MINIMAX_SEARCH_DEPTH, MINUS_INF, PLUS_INF, true).getKey();

//        tempState.getParent().printBoard();

        while (tempState!=null && tempState.getParent()!=null && tempState.getParent()!=currentState ){
            tempState = tempState.getParent();
        }

        if(tempState==null){
            System.out.println("NULL OCCURRED"); ///???????????????????????????????????????????
        }

        return tempState;
    }

    @SuppressWarnings("Duplicates")
    private Pair<State, Integer> minimax(State state, int depth, boolean maximizingPlayer){

//        if(state.isTerminal()){
//            System.out.println("Terminal State found:");    ///?
//            state.printBoard();
//        }

        if(depth == 0 || state.isTerminal()){
            return new Pair<State, Integer>(state,heuristic.evaluateState(state, playerNumber));
        }

        ArrayList<State> children = state.generateSuccessors();

        if(maximizingPlayer){
            Pair<State, Integer> maxPair = new Pair<State, Integer>(null, MINUS_INF); ///?
            while (children.size()>0){
                State child = children.remove(0);
                Pair<State, Integer> tempPair = minimax(child, depth-1, child.getTurn()==playerNumber);

                if(tempPair.getValue() > maxPair.getValue()){ ///maxPair=max(MaxPair, tempPair)
                    maxPair = tempPair;
                }

                child = null;
            }

            if(maxPair.getKey()==null){
                System.out.println("Returning null from minimax elseif at depth = " + depth); ///?
                state.printBoard();
            }

            children=null;
            state.clearSuccessors();
            return maxPair;
        }
        else{
            Pair<State, Integer> minPair = new Pair<State, Integer>(null, PLUS_INF); ///?
            while (children.size()>0){
                State child = children.remove(0);
                Pair<State, Integer> tempPair = minimax(child, depth-1, child.getTurn()==playerNumber);

                if(tempPair.getValue() < minPair.getValue()){ ///minPair=min(minPair, tempPair)
                    minPair = tempPair;
                }

                child = null;
            }

            if(minPair.getKey()==null){
                System.out.println("Returning null from minimax else at depth = " + depth); ///?
                state.printBoard();
            }

            children=null;
            state.clearSuccessors();
            return minPair;
        }
    }



    @SuppressWarnings("Duplicates")
    private Pair<State, Integer> minimaxWithPruning(State state, int depth, int alpha, int beta, boolean maximizingPlayer){

//        if(state.isTerminal()){
//            System.out.println("Terminal State found:");    ///?
//            state.printBoard();
//        }

        if(depth == 0 || state.isTerminal()){
            return new Pair<State, Integer>(state,heuristic.evaluateState(state, playerNumber));
        }

        ArrayList<State> children = state.generateSuccessors();

        if(maximizingPlayer){
            Pair<State, Integer> maxPair = new Pair<State, Integer>(null, MINUS_INF); ///?
            while (children.size()>0){
                State child = children.remove(0);
                Pair<State, Integer> tempPair = minimaxWithPruning(child, depth-1, alpha, beta, child.getTurn()==playerNumber);

                if(tempPair.getValue() > maxPair.getValue()){   ///maxPair=max(maxPair, tempPair)
                    maxPair = tempPair;
                }

                if(tempPair.getValue() > alpha){    ///alpha=max(alpha, tempValue)
                    alpha = tempPair.getValue();
                }

                if(beta <= alpha && children.size()>0){  ///pruning condition
/**                    System.out.println("Pruning " + children.size() + " nodes at depth = " + depth); **/
                    break;
                }

                child = null;
            }
            if(maxPair.getKey()==null){
                System.out.println("Returning null from minimaxWithPruning elseif at depth = " + depth); ///?
                state.printBoard();
            }

            children.clear();
            children=null;
            state.clearSuccessors();
            return maxPair;
        }
        else{
            Pair<State, Integer> minPair = new Pair<State, Integer>(null, PLUS_INF); ///?
            while (children.size()>0){
                State child = children.remove(0);
                Pair<State, Integer> tempPair = minimaxWithPruning(child, depth-1, alpha, beta, child.getTurn()==playerNumber);

                if(tempPair.getValue() < minPair.getValue()){ ///minPair=min(minPair, tempPair)
                    minPair = tempPair;
                }

                if(tempPair.getValue() < beta){    ///beta=min(beta, tempValue)
                    beta = tempPair.getValue();
                }

                if(beta <= alpha && children.size()>0){  ///pruning condition
/**                    System.out.println("Pruning " + children.size() + " nodes at depth = " + depth); **/
                    break;
                }

                child = null;
            }

            if(minPair.getKey()==null){
                System.out.println("Returning null from minimaxWithPruning else at depth = " + depth); ///?
                state.printBoard();
            }

            children.clear();
            children=null;
            state.clearSuccessors();
            return minPair;
        }
    }


}

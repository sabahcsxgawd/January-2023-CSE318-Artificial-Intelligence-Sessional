/**
 * Two players are Player0 and Player1
 *
 * Board is assumed as below:
 *      [1][5]  [1][4]  [1][3]  [1][2]  [1][1]  [1][0]
 *  [1][6]                                              [0][6]
 *      [0][5]  [0][4]  [0][3]  [0][2]  [0][1]  [0][0]
 *
 * initially 4 stones in each bin, and storage is empty
 *
 **/

package Mancala;

import Heuristics.*;

import java.util.Random;
import java.util.Scanner;

@SuppressWarnings("Duplicates")
public class MainRandomAutoplay {
    public static final int MAX_AUTOPLAY = 100;
    public static final int MAX_WEIGHT = 15;
    public static final Scanner scanner = new Scanner(System.in);
    public static final Random random = new Random();

    public static void main(String []args){
        System.out.println("******Welcome to Mancala Random Autoplay******");

        int choice0Win = 0;
        int choice1Win = 0;
        int draw = 0;

        System.out.print("Give 2 heuristics to compare (1~5): ");
        int choice0 = scanner.nextInt();
        int choice1 = scanner.nextInt();

        long startTime = System.currentTimeMillis();
        for (int i = 0; i < MAX_AUTOPLAY; i++) {
            System.out.println("\n*****AUTOPLAY NUMBER = " + (i+1) + "*****");

            int player0HeuristicNum = choice0;
            int player1HeuristicNum = choice1;

            int invert = 0;
            if(choice0!=choice1){
                invert = random.nextInt(2);     //make statistics independent of which heuristic is given first
            }

            if(invert==1){
                player0HeuristicNum = choice1;
                player1HeuristicNum = choice0;
            }

            System.out.println("Invert : " + invert);

            Heuristic player0Heuristic = getHeuristicWithRandomValues(player0HeuristicNum);
            Player player0 = new Player(0, player0Heuristic);

            Heuristic player1Heuristic = getHeuristicWithRandomValues(player1HeuristicNum);
            Player player1 = new Player(1, player1Heuristic);

            State currentState = getInitialState();

            //currentState.printBoard();
//          ArrayList<State> successors = currentState.generateSuccessors();
//          for (State state : successors) {
//              state.printBoard();
//          }

                while (!currentState.isTerminal()){
                    if(currentState.getTurn()==0){
                        currentState = player0.giveMove(currentState);
                        //System.out.println("\nAfter Player0 move: ");
                    }
                    else {
                        currentState = player1.giveMove(currentState);
                        //System.out.println("\nAfter Player1 move: ");
                    }
                    //currentState.printBoard();
                }

                int winner = currentState.getWinner();

                //System.out.println("*****Terminal State Reached*****");
                //currentState.printBoard();

                if(winner == 0){
                    System.out.println("Player0 is Winner with heuristic: " + choice0);
                    if(invert==0){
                        choice0Win++;
                    }
                    else {
                        choice1Win++;
                    }
                }
                else if(winner == 1){
                    System.out.println("Player1 is Winner with heuristic: " + choice1);
                    if(invert==1){
                        choice0Win++;
                    }
                    else {
                        choice1Win++;
                    }

                }
                else if(winner == 2){
                    System.out.println("Match Drawn!!!");
                    draw++;
                }
                else{
                    System.out.println("Terminal state is invalid");
                }

        }

        long endTime = System.currentTimeMillis();

        System.out.println();
        System.out.println("Heuristic " + choice0 + " Win = " + choice0Win + " Win Ratio = " + (100.0*choice0Win/MAX_AUTOPLAY));
        System.out.println("Heuristic " + choice1 + " Win = " + choice1Win + " Win Ratio = " + (100.0*choice1Win/MAX_AUTOPLAY));
        System.out.println("Draw = " + draw + " Draw Ratio = " + (100.0*draw/MAX_AUTOPLAY));
        System.out.println("Average Time Required = " +  (1.0*(endTime-startTime)/MAX_AUTOPLAY) + " ms");





    }

    private static Heuristic getHeuristicWithRandomValues(int choice){
        int w1, w2, w3, w4;
        switch (choice){
            case 1:
                return new Heuristic1();

            case 2:
                w1 = random.nextInt(MAX_WEIGHT)+1;
                w2 = random.nextInt(MAX_WEIGHT)+1;
                System.out.println("Heuristic 2 w1 and w2: "+ w1 + " " + w2);

                return new Heuristic2(w1, w2);

            case 3:
                w1 = random.nextInt(MAX_WEIGHT)+1;
                w2 = random.nextInt(MAX_WEIGHT)+1;
                w3 = random.nextInt(MAX_WEIGHT)+1;
                System.out.println("Heuristic 3 w1, w2 and w3: " + w1 + " " + w2 + " " + w3);

                return new Heuristic3(w1, w2, w3);

            case 4:
                w1 = random.nextInt(MAX_WEIGHT)+1;
                w2 = random.nextInt(MAX_WEIGHT)+1;
                w3 = random.nextInt(MAX_WEIGHT)+1;
                w4 = random.nextInt(MAX_WEIGHT)+1;
                System.out.println("Heuristic 4 w1, w2, w3 and w4: " + w1 + " " + w2 + " " + w3 + " " + w4);

                return new Heuristic4(w1, w2, w3, w4);

            case 5:
                w1 = random.nextInt(MAX_WEIGHT)+1;
                w2 = random.nextInt(MAX_WEIGHT)+1;
                w3 = random.nextInt(MAX_WEIGHT)+1;
                w4 = random.nextInt(MAX_WEIGHT)+1;
                System.out.println("Heuristic 5 w1, w2, w3 and w4: " + w1 + " " + w2 + " " + w3 + " " + w4);

                return new Heuristic5(w1, w2, w3, w4);

            default:
                System.out.println("Wrong choice of heuristic. Default heuristic set...");
                return new Heuristic1();


        }


    }

    private static State getInitialState(){
        State state = new State(0, null);
        ///Initialize
        int [][]newBoard = new int[7][7];

        for (int i = 0; i < 6; i++) {
            newBoard[0][i] = 4;
            newBoard[1][i] = 4;
        }
        newBoard[0][6] = 0;
        newBoard[1][6] = 0;

        state.setBoard(newBoard);

        return state;
    }


}

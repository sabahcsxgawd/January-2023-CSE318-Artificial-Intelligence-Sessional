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

import java.util.Scanner;

@SuppressWarnings("Duplicates")
public class Main {
    public static final int MINIMAX_SEARCH_DEPTH = 13;
    public static final Scanner scanner = new Scanner(System.in);

    public static void main(String []args){
        System.out.println("******Welcome to Mancala******");



        System.out.print("Give Player0 heuristic (1~5): ");
        int choice0 = scanner.nextInt();
        Heuristic player0Heuristic = getHeuristic(choice0);
        Player player0 = new Player(0, player0Heuristic);

        System.out.print("Give Player1 heuristic (1~5): ");
        int choice1 = scanner.nextInt();
        Heuristic player1Heuristic = getHeuristic(choice1);
        Player player1 = new Player(1, player1Heuristic);


        State currentState = getInitialState();

        currentState.printBoard();
//        ArrayList<State> successors = currentState.generateSuccessors();
//        for (State state : successors) {
//            state.printBoard();
//        }

        while (!currentState.isTerminal()){
            if(currentState.getTurn()==0){
                currentState = player0.giveMove(currentState);
                System.out.println("\nAfter Player0 move: ");
            }
            else {
                currentState = player1.giveMove(currentState);
                System.out.println("\nAfter Player1 move: ");
            }
            currentState.printBoard();
        }

        int winner = currentState.getWinner();

        System.out.println("*****Terminal State Reached*****");
        currentState.printBoard();

        if(winner == 0){
            System.out.println("Player0 is Winner with heuristic: " + choice0);
        }
        else if(winner == 1){
            System.out.println("Player1 is Winner with heuristic: " + choice1);

        }
        else if(winner == 2){
            System.out.println("Match Drawn!!!");
        }
        else{
            System.out.println("Terminal state is invalid");
        }



    }


    private static Heuristic getHeuristic(int choice){
        int w1, w2, w3, w4;
        switch (choice){
            case 1:
                return new Heuristic1();

            case 2:
                System.out.print("Enter values of w1 and w2: ");
                w1 = scanner.nextInt();
                w2 = scanner.nextInt();
                System.out.println("Heuristic 2 w1 and w2: "+ w1 + " " + w2);

                return new Heuristic2(w1, w2);

            case 3:
                System.out.print("Enter values of w1, w2 and w3: ");
                w1 = scanner.nextInt();
                w2 = scanner.nextInt();
                w3 = scanner.nextInt();
                System.out.println("Heuristic 3 w1, w2 and w3: " + w1 + " " + w2 + " " + w3);

                return new Heuristic3(w1, w2, w3);

            case 4:
                System.out.print("Enter values of w1, w2, w3 and w4: ");
                w1 = scanner.nextInt();
                w2 = scanner.nextInt();
                w3 = scanner.nextInt();
                w4 = scanner.nextInt();
                System.out.println("Heuristic 4 w1, w2, w3 and w4: " + w1 + " " + w2 + " " + w3 + " " + w4);

                return new Heuristic4(w1, w2, w3, w4);

            case 5:
                System.out.print("Enter values of w1, w2, w3 and w4: ");
                w1 = scanner.nextInt();
                w2 = scanner.nextInt();
                w3 = scanner.nextInt();
                w4 = scanner.nextInt();
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

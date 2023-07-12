package Mancala;

import java.util.ArrayList;

public class State {
    private int turn;
    private int [][]board;
    private ArrayList<State> successors;

    private State parent;

    State(int turn, State p) {
        this.turn = turn;

        this.board = new int[7][7];
        //this.successors = new ArrayList<State>();

        this.parent = p;
    }

    int getTurn() {
        return turn;
    }

    public void setTurn(int turn) {
        this.turn = turn;
    }

    private int[][] getBoard() {
        int [][]newBoard = new int[7][7];
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                newBoard[i][j] = this.board[i][j];
            }
        }
        return newBoard;
    }

    void setBoard(int[][] newBoard) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                this.board[i][j] = newBoard[i][j];
            }
        }
    }

    public void clearBoard(){
        board = null;
    }

    public ArrayList<State> getSuccessors() {
        return new ArrayList<State>(successors);
    }

    private void setSuccessors(ArrayList<State> successors) {
        if(successors==null){
            this.successors = new ArrayList<State>();
        }
        else {
            this.successors = new ArrayList<State>(successors);
        }
    }

    void clearSuccessors(){
        if(successors!=null){
            successors.clear();
        }

        successors = null;
    }

    State getParent() {
        return parent;
    }

    public void setParent(State parent) {
        this.parent = parent;
    }

    boolean isTerminal(){
        boolean flag0 = true;
        boolean flag1 = true;
        for (int i = 0; i < 6; i++) {
            if(board[0][i] > 0){
                flag0 = false;
            }
            if(board[1][i] > 0){
                flag1 = false;
            }
        }

        return  (flag0 || flag1);
    }

    void printBoard(){
        System.out.println("Printing Mancala board with turn " + turn + " :");

        ///printing upper line
        for (int i = 5; i >=0 ; i--) {
            System.out.print("\t" + board[1][i]);
        }
        System.out.println();

        //printing two storage
        System.out.println(board[1][6] +"\t\t\t\t\t\t\t" + board[0][6]);

        ///printing lower line
        for (int i = 0; i < 6 ; i++) {
            System.out.print("\t" + board[0][i]);
        }
        System.out.println("\n");


    }

    public int getStorageDiff(int playerNumber){
        return (board[playerNumber][6] - board[playerNumber^1][6]);
    }

    public int getBinsDiff(int playerNumber){
        int diff = 0;
        for (int i = 0; i < 6; i++) {
            diff += board[playerNumber][i] - board[playerNumber^1][i];
        }

        return diff;
    }

    public int getCloseToStorageDiff(int playerNumber){
        int diff = 0;

        for (int i = 0; i < 6; i++) {
            diff += (6-i)*board[playerNumber][i] - (i+1)*board[playerNumber^1][i];
        }

        return diff;
    }

    public int extraTurn(int playerNumber){
        if(parent==null){
            return 0;
        }
        else if(parent.getTurn()==playerNumber && this.getTurn()==playerNumber){ //player gets an extra turn
            return 1;
        }
        else if(parent.getTurn()==this.getTurn()){  //opponent gets an extra turn
            return -1;
        }
        else {
            return 0;
        }
    }

    public int numStoneCaptured(int playerNumber){
        if(parent==null){
            return this.board[playerNumber][6];
        }
        else if(parent.getTurn() == playerNumber){  //parent.turn represents who captured stones to reach this state
            return (this.board[playerNumber][6] - parent.board[playerNumber][6]);
        }
        else{   //negative means this turn is adverse for player
            return -(this.board[playerNumber^1][6] - parent.board[playerNumber^1][6]);
        }
    }

    private void finalizeBoard(){
        for (int i = 0; i < 6; i++) {
            board[0][6] = board[0][6] + board[0][i];
            board[0][i] = 0;
            board[1][6] = board[1][6] + board[1][i];
            board[1][i] = 0;
        }

    }

    int getWinner(){
        if(!isTerminal()){  //invalid check
            return -1;
        }

        finalizeBoard();
        if(getStorageDiff(0) > 0){  //winner: player0
            return 0;
        }
        else if(getStorageDiff(1) > 0){ //winner: player1
            return 1;
        }
        else{   //draw
            return 2;
        }
    }

    ArrayList<State> generateSuccessors(){
        ArrayList<State> tempSuccessors = new ArrayList<State>();

        for (int i = 0; i < 6; i++) {
            if(board[turn][i] <=0){
                continue;
            }

            int stone = board[turn][i];
            int row = turn;
            int col = i;

            int [][]tempBoard = getBoard();
            tempBoard[turn][i] = 0;

            int tempTurn = turn^1;

            while (stone>0){
                if(col==6){
                    col=0;
                    row ^= 1;
                }
                else {
                    col++;
                }

                tempBoard[row][col] = tempBoard[row][col]+1;

                stone--;

                if(stone==0){ //last stone placed
                    if (row == turn && col < 6 && tempBoard[row][col] == 1 && tempBoard[row^1][5-col] > 0){  //last stone falls in empty bin and opposite bin has stones
                        tempBoard[row][6] = tempBoard[row][6]+tempBoard[row][col]+tempBoard[row^1][5-col];
                        tempBoard[row][col] = 0;
                        tempBoard[row^1][5-col] = 0;
//                        System.out.println("Capturing opposite stones");
                    }
                    else if(row == turn && col == 6){  //last stone falls in storage
                        tempTurn = turn;
//                        System.out.println("Found extra turn");
                    }
                }

            }

            State tempState = new State(tempTurn, this);
            tempState.setBoard(tempBoard);

            tempSuccessors.add(tempState);


        }


        setSuccessors(tempSuccessors);
        return tempSuccessors;
    }

}

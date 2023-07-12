package N_Puzzle;

import javafx.util.Pair;

import java.util.ArrayList;

public class SupportingFunctions {

    private static Pair<Integer, Integer> getNumberInverse(int array[][]){  //<number of inverse, row number of space>
        ArrayList<Integer> numbers = new ArrayList<Integer>();

        int numInv = 0;
        int spaceRowNum = 0;

        for(int i=0; i<Main.k; i++){
            for (int j=0; j<Main.k; j++) {
                if(array[i][j]==Main.SPACE){
                    spaceRowNum = i;
                    continue;
                }
                numbers.add(array[i][j]);
            }
        }

        for(int i=0; i<numbers.size(); i++){
            for (int j=i+1; j<numbers.size(); j++) {

                if(numbers.get(i) > numbers.get(j)){
                    numInv++;
                }

            }
        }

        System.out.println("Number of Inverses = " + numInv);

        return new Pair<Integer, Integer>(numInv, spaceRowNum);

    }


    public static boolean isSolvable(int array[][]){

        Pair<Integer, Integer> inv = getNumberInverse(array);

        if( Main.k%2==1 && inv.getKey()%2==1 ){ //odd board size, odd number of inverse
            return false;
        }
        else if(Main.k%2==0 && (inv.getKey()+inv.getValue())%2==0 ){ //even board size,
            return false;
        }
        else {
            return true;
        }

    }

    public static int[][] copyArray(int array[][]){
        int tempArr[][] = new int[Main.k][Main.k];

        for(int i=0; i<Main.k; i++){
            for (int j=0; j<Main.k; j++) {
                tempArr[i][j] = array[i][j];
            }
        }

        return tempArr;
    }

    public static int[][] swap(int array[][], int i1, int j1, int i2, int j2){

        //System.out.println(i1 + " " + j1 + " " +j1 + " " +j2);

        int tempArr[][] = copyArray(array);

        tempArr[i1][j1] = array[i2][j2];
        tempArr[i2][j2] = array[i1][j1];

        return tempArr;
    }

    public static int[][] swap(int array[][], Pair<Integer, Integer> pos1, Pair<Integer, Integer> pos2){

        //System.out.println(pos1.getKey() + " " + pos1.getValue() + " " +pos2.getKey() + " " +pos2.getValue());

        int tempArr[][] = copyArray(array);

        tempArr[pos1.getKey()][pos1.getValue()] = array[pos2.getKey()][pos2.getValue()];
        tempArr[pos2.getKey()][pos2.getValue()] = array[pos1.getKey()][pos1.getValue()];

        return tempArr;
    }

    private static int getCorrectValue(Pair<Integer, Integer> pos){
        if(pos.getKey()==Main.k-1 && pos.getValue()==Main.k-1 ){
            return Main.SPACE;
        }
        else{
            return Main.k*pos.getKey()+pos.getValue()+1;
        }
    }

    private static Pair<Integer, Integer> getCorrectPosition(int val){
        if(val == Main.SPACE)
            return null;

        return new Pair<Integer, Integer>( (val-1)/Main.k , (val-1)%Main.k);
    }

    public static int getHammingDistance(int array[][]){
        int dist = 0;

        for(int i=0; i<Main.k; i++){
            for (int j=0; j<Main.k; j++) {
                if(i==Main.k-1 && j==Main.k-1){
                    continue;
                }
                else if(array[i][j]!=getCorrectValue(new Pair<Integer, Integer>(i,j))){
                    dist++;
                }
            }
        }

        return dist;
    }

    public static int getManhattanDistance(int array[][]){
        int dist = 0;

        for(int i=0; i<Main.k; i++){
            for (int j=0; j<Main.k; j++) {
                if(array[i][j] == Main.SPACE){
                    continue;
                }

                Pair<Integer,Integer> correctPosition = getCorrectPosition(array[i][j]);

                if(correctPosition==null){
                    continue;
                }

                dist+=Math.abs(i-correctPosition.getKey()) + Math.abs(j-correctPosition.getValue());

                //System.out.println("Calculating manhattan distance : " + array[i][j] + " " + correctPosition.getKey() + " " + correctPosition.getValue() + " " + dist);

            }
        }

        return dist;

    }

    public static int getLinearConflicts(int array[][]){    //not done
        int dist = getManhattanDistance(array);

        for(int i=0; i<Main.k; i++){
            for (int j=0; j<Main.k; j++) {
                if(array[i][j]==Main.SPACE){
                    continue;
                }
                Pair <Integer, Integer> pos1 = getCorrectPosition(array[i][j]);
                if (pos1.getKey()!=i){
                    continue;
                }

                for (int k=j+1; k<Main.k; k++) {
                    if(array[i][k]==Main.SPACE){
                        continue;
                    }
                    Pair <Integer, Integer> pos2 = getCorrectPosition(array[i][k]);
                    if (pos2.getKey()!=i){
                        continue;
                    }
                    else if(array[i][j] > array[i][k]){
                        dist+=2;
                    }

                }
            }
        }

        for(int j=0; j<Main.k; j++){
            for (int i=0; i<Main.k; i++) {
                if(array[i][j]==Main.SPACE){
                    continue;
                }
                Pair <Integer, Integer> pos1 = getCorrectPosition(array[i][j]);
                if (pos1.getValue()!=j){
                    continue;
                }
                for (int k=i+1; k<Main.k; k++) {
                    if(array[k][j]==Main.SPACE){
                        continue;
                    }
                    Pair <Integer, Integer> pos2 = getCorrectPosition(array[k][j]);
                    if (pos2.getValue()!=j){
                        continue;
                    }
                    else if(array[i][j] > array[k][j]){
                        dist+=2;
                    }

                }



            }
        }


        return dist;

    }



}

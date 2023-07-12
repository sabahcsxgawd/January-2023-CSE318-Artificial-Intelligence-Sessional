package N_Puzzle;

import javafx.util.Pair;

import java.io.File;
import java.io.FileInputStream;
import java.util.Scanner;

public class Main {

    public static int k;
    public static final int SPACE = 0;

    public static int array[][];

    public static void main(String[] args) {
        Solution solution;

        try {
            File input = new File("Input.txt");
            if(input.exists()){
                System.out.println("Input file found!");
            }
            else{
                System.out.println("Input file not found. Exiting...");
                return;
            }

            Scanner scanner = new Scanner(new FileInputStream(input));

            k = scanner.nextInt();
            scanner.nextLine();

            array = new int[k][k];

            for(int i=0; i<k; i++){
                for (int j=0; j<k; j++) {
                    array[i][j] = 0;
                }
            }

            Pair<Integer, Integer> sp = new Pair<Integer, Integer>(-1, -1);

            //taking array input
            for(int i=0; i<k; i++){
                String str = scanner.nextLine();
                String []nums = str.split(" ");

                //System.out.println(nums.length);

                if(nums.length==k){
                    for (int j=0; j<k; j++){
                        array[i][j] = Integer.parseInt(nums[j]);
                    }
                }
                else if(nums.length<k){

                    for (int j=0; j<nums.length; j++){
                        array[i][j] = Integer.parseInt(nums[j]);
                    }
                    array[i][k-1] = SPACE;
                    sp = new Pair<Integer, Integer>(i, k-1);
                }
                else{
                    int x =0;
                    for (int j=0; j<nums.length; j++){
                        if(nums[j].length()==0){
                            array[i][x] = SPACE;
                            sp = new Pair<Integer, Integer>(i, x);
                            x++;
                            j++;
                            continue;
                        }
                        array[i][x] = Integer.parseInt(nums[j]);
                        x++;
                    }
                }

            }



            if(!SupportingFunctions.isSolvable(array)){     //checking whether solvable or not
                System.out.println("Input is not solvable. Exiting...");
                return;
            }

            System.out.println();


            System.out.println("Starting Solution with Linear Conflict...");
            solution = new LinConflict(array, sp);
            Node resultLin = solution.solve();

            if(resultLin==null){
                System.out.println("Unexpectedly solution not found with Linear Conflicts");
            }
            else {
                System.out.println("Solution found at distance: " + resultLin.getDist());
                System.out.println("Printing solution steps with Linear Conflicts: ");
                resultLin.printSteps();
            }


            System.out.println("Starting Solution with Manhattan Distance...");
            solution = new ManDist(array, sp);
            Node resultMan = solution.solve();

            if(resultMan==null){
                System.out.println("Unexpectedly solution not found with Manhattan Distance");
            }
            else {
                System.out.println("Solution found at distance: " + resultMan.getDist());
                System.out.println("Printing solution steps with Manhattan Distance: ");
                resultMan.printSteps();
            }



            System.out.println("Starting Solution with Hamming Distance...");
            solution = new HamDist(array, sp);
            Node resultHam = solution.solve();

            if(resultHam==null){
                System.out.println("Unexpectedly solution not found with Hamming Distance");
            }
            else {
                System.out.println("Solution found at distance: " + resultHam.getDist());
                System.out.println("Printing solution steps with Hamming Distance: ");
                resultHam.printSteps();
            }



        } catch (Exception e) {
            e.printStackTrace();
        }


    }
}

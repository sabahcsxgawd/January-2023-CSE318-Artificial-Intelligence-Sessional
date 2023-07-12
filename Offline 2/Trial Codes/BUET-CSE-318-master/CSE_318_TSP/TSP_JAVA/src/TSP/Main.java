package TSP;

import javafx.util.Pair;
import java.io.File;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;
import java.util.Scanner;

public class Main {
    public static final int SIMPLE_ITR = 5; //5
    public static final int RANDOM_ITR = 10; //10
    public static final int MAX_CANDIDATES = 5; //5
    public static final int OPT_CANDIDATES = 3;
    public static final Random rand = new Random();


    public static int MAX_ITR = SIMPLE_ITR;
    public static boolean RANDOMIZED_START = true;
    public static int USE_CANDIDATES = 1;

    public static int constructionWrongSolution = 0;
    public static int optimizationWrongSolution = 0;

    public static int n;
    public static double optimalResult;
    public static int startCity;
    public static ArrayList<Pair<Float, Float>> locations;

    public static void main(String []args){
        System.out.println("Travelling Salesman Problem");

        int constructionChoice, optimizationChoice;
        Scanner sc = new Scanner(System.in);

        System.out.println("Construction Heuristic: 1.Nearest Neighbor\t2.Savings");
        constructionChoice = sc.nextInt();

        sc.close();

        try{
            File input = new File("Input.txt");
            if(input.exists()){
                System.out.println("Input file found!");
            }
            else{
                System.out.println("Input file not found. Exiting...");
                return;
            }

            Scanner scanner = new Scanner(new FileInputStream(input));

            //=============================================================
            //Input
            //=============================================================

            System.out.println("Taking Inputs...");

//            while(scanner.hasNextLine()){
//                System.out.println(scanner.nextLine());
//            }

            n = scanner.nextInt();
            optimalResult = scanner.nextDouble();
            System.out.println(n + " cities in the problem.\nLocations are:");

            locations = new ArrayList<Pair<Float, Float>>();

            int idx;
            float x, y;
            for (int i = 0; i < n; i++) {
                idx = scanner.nextInt();    //for complying with test case format
                x = scanner.nextFloat();
                y = scanner.nextFloat();

                locations.add(new Pair<>(x, y));
                System.out.println(locations.get(i).getKey() + " " + locations.get(i).getValue());

            }

            scanner.close();


            //=============================================================
            //CHOOSING START CITY
            //=============================================================
            ArrayList<Solution> solutions = new ArrayList<Solution>();

            double avgSimpleDist = 0;
            double avgSimpleDuration = 0;
            double minSimpleDist = 999999999;
            int minSimpleIdx = -1;
            Solution minSimpleSolution;
            double maxSimpleDist = -1;
            int maxSimpleIdx = -1;
            Solution maxSimpleSolution;


            if(constructionChoice == 1 ){
                //=============================================================
                //Nearest Neighbor Heuristic Construction
                //=============================================================
                System.out.println("Starting Simple Nearest Neighbor Heuristic Construction...");
                System.out.println();

                for (int i = 0; i < MAX_ITR; i++) {
                    System.out.println("Running " + (i+1) + "th iteration...");
                    Solution s = new NearestNeighbor();
                    solutions.add(s);
                    s.construct();
                }

            }
            else if(constructionChoice == 2){
                //=============================================================
                //Savings Heuristic Construction
                //=============================================================
                System.out.println("Starting Simple Savings Heuristic Construction...");
                System.out.println();

                for (int i = 0; i < MAX_ITR; i++) {
                    System.out.println("Running " + (i+1) + "th iteration...");
                    Solution s = new Savings();
                    solutions.add(s);
                    s.construct();
                }

            }
            else{
                System.out.println("Wrong choice of Construction Heuristic");
            }

            for (int i = 0; i < MAX_ITR; i++) {
                Solution s = solutions.get(i);

                avgSimpleDist += s.getTotalDistanceTravelled() / MAX_ITR;
                avgSimpleDuration += s.getConstructionDuration()*1.0 / MAX_ITR;

                if(s.getTotalDistanceTravelled() < minSimpleDist){
                    minSimpleDist = s.getTotalDistanceTravelled();
                    minSimpleIdx = i;
                }

                if(s.getTotalDistanceTravelled() > maxSimpleDist){
                    maxSimpleDist = s.getTotalDistanceTravelled();
                    maxSimpleIdx = i;
                }

                System.out.println("Printing " + (i+1) +"th solution of Greedy Simple Version...");
                s.printConstruction();

            }

            minSimpleSolution = solutions.get(minSimpleIdx);
            maxSimpleSolution = solutions.get(maxSimpleIdx);

            //=============================================================
            //Initializing variables for constructions from startCity
            //=============================================================

            startCity = minSimpleSolution.getStartCityIdx();
            RANDOMIZED_START = false;
            USE_CANDIDATES = MAX_CANDIDATES;
            MAX_ITR = RANDOM_ITR;
            solutions.clear();


            double avgRandomDist = 0;
            double avgRandomDuration = 0;
            Solution minRandomSolution;
            Solution maxRandomSolution;


            //=============================================================
            //FINDING BEST TOUR FROM START CITY
            //=============================================================


            if(constructionChoice == 1 ){
                //=============================================================
                //Nearest Neighbor Heuristic Construction
                //=============================================================
                System.out.println("Starting Random Nearest Neighbor Heuristic Construction...");
                System.out.println();

                for (int i = 0; i < MAX_ITR; i++) {
                    System.out.println("Running " + (i+1) + "th iteration...");
                    Solution s = new NearestNeighbor();
                    solutions.add(s);
                    s.construct();
                }

            }
            else if(constructionChoice == 2){
                //=============================================================
                //Savings Heuristic Construction
                //=============================================================
                System.out.println("Starting Random Savings Heuristic Construction...");
                System.out.println("Start city is set to : " + (startCity+1));
                System.out.println();

                for (int i = 0; i < MAX_ITR; i++) {
                    System.out.println("Running " + (i+1) + "th iteration...");
                    Solution s = new Savings();
                    solutions.add(s);
                    s.construct();
                }

            }
            else{
                System.out.println("Wrong choice of Construction Heuristic");
            }



//            solutions.sort(new Comparator<Pair<Pair<Integer, Integer>, Float>>() {
//                @Override
//                public int compare(Pair<Pair<Integer, Integer>, Float> o2, Pair<Pair<Integer, Integer>, Float> o1) {
//                    return Float.compare(o1.getValue(), o2.getValue()) ;
//                }
//            });

            for (int i = 0; i < MAX_ITR; i++) {
                Solution s = solutions.get(i);

                avgRandomDist += s.getTotalDistanceTravelled() / MAX_ITR;
                avgRandomDuration += s.getConstructionDuration()*1.0 / MAX_ITR;

                System.out.println("Printing " + (i+1) +"th solution of Greedy Randomized Version...");
                s.printConstruction();

            }

            solutions.sort(new Comparator<Solution>() {     //to get best 3 solutions to optimize
                @Override
                public int compare(Solution o1, Solution o2) {
                    return Double.compare(o1.getTotalDistanceTravelled(), o2.getTotalDistanceTravelled());

                }
            });

            minRandomSolution = solutions.get(0);
            maxRandomSolution = solutions.get(solutions.size()-1);


            //=============================================================
            //OPTIMIZE 2-OPT BEST
            //=============================================================

            System.out.println("Starting Two-opt Best Improvement...");
            System.out.println();

            ArrayList<Solution> optCandidatesBest = new ArrayList<Solution>();
            double avgKOptBestDist = 0;
            double avgKOptBestDuration = 0;
            Solution minKOptBestSolution;
            Solution maxKOptBestSolution;

            for (int i = 0; i < OPT_CANDIDATES && i < solutions.size(); i++) {
                optCandidatesBest.add(new Two_Opt_Best(solutions.get(i).copySolution()));
                System.out.println("COST BEFORE BEST IMPROVEMENT : " + optCandidatesBest.get(i).getTotalDistanceTravelled());
                optCandidatesBest.get(i).improve();
                optCandidatesBest.get(i).printOptimization();
            }

            for (int i = 0; i < OPT_CANDIDATES; i++) {
                Solution s = optCandidatesBest.get(i);

                avgKOptBestDist += s.getTotalDistanceTravelled() / MAX_ITR;
                avgKOptBestDuration += s.getOptimizationDuration()*1.0 / MAX_ITR;

            }

            optCandidatesBest.sort(new Comparator<Solution>() {
                @Override
                public int compare(Solution o1, Solution o2) {
                    return Double.compare(o1.getTotalDistanceTravelled(), o2.getTotalDistanceTravelled());

                }
            });

            minKOptBestSolution = optCandidatesBest.get(0);
            maxKOptBestSolution = optCandidatesBest.get(optCandidatesBest.size()-1);


            //=============================================================
            //OPTIMIZE 2-OPT FIRST
            //=============================================================

            System.out.println("Starting Two-opt First Improvement...");
            System.out.println();

            ArrayList<Solution> optCandidatesFirst = new ArrayList<Solution>();
            double avgKOptFirstDist = 0;
            double avgKOptFirstDuration = 0;
            Solution minKOptFirstSolution;
            Solution maxKOptFirstSolution;


            for (int i = 0; i < OPT_CANDIDATES && i < solutions.size(); i++) {
                optCandidatesFirst.add(new Two_Opt_First(solutions.get(i).copySolution()));
                System.out.println("COST BEFORE FIRST IMPROVEMENT : " + optCandidatesFirst.get(i).getTotalDistanceTravelled());
                optCandidatesFirst.get(i).improve();
                optCandidatesFirst.get(i).printOptimization();
            }

            for (int i = 0; i < OPT_CANDIDATES; i++) {
                Solution s = optCandidatesFirst.get(i);

                avgKOptFirstDist += s.getTotalDistanceTravelled() / MAX_ITR;
                avgKOptFirstDuration += s.getOptimizationDuration()*1.0 / MAX_ITR;

            }

            optCandidatesFirst.sort(new Comparator<Solution>() {
                @Override
                public int compare(Solution o1, Solution o2) {
                    return Double.compare(o1.getTotalDistanceTravelled(), o2.getTotalDistanceTravelled());

                }
            });

            minKOptFirstSolution = optCandidatesFirst.get(0);
            maxKOptFirstSolution = optCandidatesFirst.get(optCandidatesFirst.size()-1);



            //=============================================================
            //SHOWING RESULTS
            //=============================================================
            System.out.println();
            System.out.println();
            System.out.println("**********************************************************************R E S U L T**********************************************************************");
            System.out.println();
            System.out.println();

            //GREEDY SIMPLE RESULT
            System.out.println("***FINAL RESULTS OF GREEDY SIMPLE VERSION****");
            System.out.println("Average Time required for construction in Greedy Simple Version = " + avgSimpleDuration + "ms");
            System.out.println("Average Distance Travelled in Greedy Simple Version = " + avgSimpleDist);
            System.out.println();

            System.out.println("Best Solution in Greedy Simple Version:");
            minSimpleSolution.printConstruction();

            System.out.println("Worst Solution in Greedy Simple Version:");
            maxSimpleSolution.printConstruction();

            System.out.println();


            //GREEDY RANDOM RESULT
            System.out.println("***FINAL RESULTS OF GREEDY RANDOMIZED VERSION****");
            System.out.println("Average Time required for construction in Greedy Randomized Version = " + avgRandomDuration + "ms");
            System.out.println("Average Distance Travelled in Greedy Randomized Version = " + avgRandomDist);
            System.out.println();

            System.out.println("Best Solution in Greedy Randomized Version:");
            minRandomSolution.printConstruction();

            System.out.println("Worst Solution in Greedy Randomized Version:");
            maxRandomSolution.printConstruction();

            System.out.println();


            //BEST IMPROVEMENT TWO OPT OPTIMIZATION RESULTS
            System.out.println("***FINAL RESULTS OF BEST IMPROVEMENT TWO OPT OPTIMIZATION****");
            System.out.println("Average Time required for optimization by Best Improvement version = " + avgKOptBestDuration + "ms");
            System.out.println("Average Distance Travelled in optimization by Best Improvement version = " + avgKOptBestDist);
            System.out.println();

            System.out.println("Best Solution in optimization by Best Improvement version:");
            minKOptBestSolution.printOptimization();

            System.out.println("Worst Solution in optimization by Best Improvement version:");
            maxKOptBestSolution.printOptimization();


            //FIRST IMPROVEMENT TWO OPT OPTIMIZATION RESULTS
            System.out.println("***FINAL RESULTS OF FIRST IMPROVEMENT TWO OPT OPTIMIZATION****");
            System.out.println("Average Time required for optimization by First Improvement Version = " + avgKOptFirstDuration + "ms");
            System.out.println("Average Distance Travelled in optimization by First Improvement version  = " + avgKOptFirstDist);
            System.out.println();

            System.out.println("Best Solution in optimization by First Improvement version:");
            minKOptFirstSolution.printOptimization();

            System.out.println("Worst Solution in optimization by First Improvement version:");
            maxKOptFirstSolution.printOptimization();


            //Result Percentage
            System.out.println("Actual Cost = " + optimalResult + ", Percentage = " + 100 + "%");
            System.out.println("Best Improvement Cost = " + minKOptBestSolution.getTotalDistanceTravelled() + ", Percentage = " + 100*minKOptBestSolution.getTotalDistanceTravelled()/optimalResult + "%");
            System.out.println("First Improvement Cost = " + minKOptFirstSolution.getTotalDistanceTravelled() + ", Percentage = " +  100*minKOptFirstSolution.getTotalDistanceTravelled()/optimalResult  + "%");

            //checking correctness
            System.out.println();
            System.out.println("Number of Construction Wrong Solutions = " + constructionWrongSolution);
            System.out.println("Number of Optimization Wrong Solutions = " + optimizationWrongSolution);


        }catch (Exception e){
            e.printStackTrace();
        }



    }

    public static float calculateDistance(int i, int j){
        float x1 = locations.get(i).getKey();
        float y1 = locations.get(i).getValue();

        float x2 = locations.get(j).getKey();
        float y2 = locations.get(j).getValue();

        return (float) Math.sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    }

}

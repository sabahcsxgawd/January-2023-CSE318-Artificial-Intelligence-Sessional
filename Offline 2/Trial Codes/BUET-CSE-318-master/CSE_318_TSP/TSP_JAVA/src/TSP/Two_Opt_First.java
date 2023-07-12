package TSP;

import java.util.ArrayList;

public class Two_Opt_First extends Solution {
    private long startTime;


    public Two_Opt_First(Solution solution) {
        super();

        startCityIdx = solution.getStartCityIdx();
        tourCityIdx.addAll(solution.tourCityIdx);
        constructionDuration = solution.getConstructionDuration();
        totalDistanceTravelled = solution.getTotalDistanceTravelled();
        numberOfRoadsTravelled = solution.getNumberOfRoadsTravelled();

        solution = null;

    }

    @Override
    void construct() {
        //doing nothing here
    }

    @Override
    void improve() {
        System.out.println("Starting Optimization in Two Opt Heuristic");
        startTime = System.currentTimeMillis();

        ArrayList<Integer> currentTour = new ArrayList<>(tourCityIdx);
        double currentTourCost = calculateTourCost(currentTour);

        for(int i=1; i<Main.n-1; i++){
            for(int j=i+1; j<Main.n; j++){
                ArrayList <Integer> tempTour = reversePath(currentTour, i, j);
                double tempTourCost = calculateTourCost(tempTour);

                if(tempTourCost < currentTourCost){
                    currentTour = tempTour;
                    currentTourCost = tempTourCost;

                    //System.out.println("OPTIMIZED WITH INDICES: " + i + " AND " + j);

                    i--;
                    break;
                }

            }
        }

        tourCityIdx = currentTour;
        totalDistanceTravelled = currentTourCost;

        if(!checkSolution()){
            Main.optimizationWrongSolution++;
        }



        optimizationDuration = System.currentTimeMillis() - startTime;

        System.out.println("Finished First Improvement in Two opt Heuristic");
        System.out.println();



    }

    ArrayList<Integer> reversePath(ArrayList<Integer> currentTour, int l, int u){
        ArrayList<Integer> tempTour = new ArrayList<Integer>(currentTour);
        for (int i = l; i <= u; i++) {
            tempTour.set(i, currentTour.get(u-i+l));
        }
        return tempTour;
    }

    double calculateTourCost(ArrayList<Integer> tour){
        double cost = 0;
        for (int i = 0; i < tour.size()-1; i++) {
            cost+= Main.calculateDistance(tour.get(i), tour.get(i+1));
        }

        return cost;
    }

}

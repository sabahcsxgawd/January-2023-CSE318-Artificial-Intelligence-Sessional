package TSP;

import javafx.util.Pair;

import java.util.ArrayList;

class NearestNeighbor extends Solution {
    private int numberOfCitiesVisited;

    private long startTime;

    private boolean []visited;

    NearestNeighbor(){
        super();

        if (Main.RANDOMIZED_START){
            startCityIdx =  Main.rand.nextInt(Main.n);
        }
        else{
            startCityIdx = Main.startCity;
        }

        tourCityIdx.add(startCityIdx);
        System.out.println("Starting City: " + startCityIdx);

        numberOfCitiesVisited = 1;  //start city is visited

        visited = new boolean[Main.n];
        for (int i = 0; i < Main.n; i++) {
            visited[i] = false;
        }
        visited[startCityIdx] = true;

    }

    private ArrayList<Pair<Integer, Float>> calculateCandidateNeighbors(int currentCityIdx){ //O(n*USE_CANDIDATES) sort
        ArrayList<Pair<Integer, Float>> candidates = new ArrayList<Pair<Integer, Float>>();
        ArrayList<Integer> takenCities = new ArrayList<Integer>();

        //=============================================================
        //Calculating all cities distance from current city
        //=============================================================
        float [] distanceArray = new float[Main.n];
        for (int j = 0; j < Main.n; j++) {
            distanceArray[j] = Main.calculateDistance(j, currentCityIdx);
        }

        //=============================================================
        //Gathering candidates
        //=============================================================
        double prevMin = -1;
        for (int i = 0; i < Main.USE_CANDIDATES; i++) {
            float minVal = 999999999;
            int minIdx = -1;

            for (int j = 0; j < Main.n; j++) {
                if( j==currentCityIdx || visited[j]){
                    continue;
                }

                float val = distanceArray[j];
                if(val < minVal && val >= prevMin && !takenCities.contains(j)){
                    minVal = val;
                    minIdx = j;
                }

            }

            if(minIdx==-1){ //no suitable candidates found
                break;
            }

            candidates.add(new Pair<>(minIdx, minVal) );
            takenCities.add(minIdx);
            prevMin = minVal;

        }

        return candidates;
    }

    @Override
    void construct() {
        System.out.println("Starting Construction in Nearest Neighbor Heuristic");
        startTime = System.currentTimeMillis();

        int currentCityIdx = startCityIdx;

        //=============================================================
        //Going to Random Candidate
        //=============================================================
        while(numberOfCitiesVisited!=Main.n){
            ArrayList<Pair<Integer, Float>> candidateCities = calculateCandidateNeighbors(currentCityIdx);
            int randIdx = Main.rand.nextInt(candidateCities.size());

//            System.out.print("Candidates are : ");
//            for (Pair<Integer, Float> entry: candidateCities) {
//                System.out.print(entry.getKey() + " ");
//            }
//            System.out.println();

            int nextCityIdx = candidateCities.get(randIdx).getKey();
            float nextCityDist = candidateCities.get(randIdx).getValue();

            tourCityIdx.add(nextCityIdx);
            visited[nextCityIdx] = true;
            totalDistanceTravelled += nextCityDist;
            numberOfRoadsTravelled++;
            numberOfCitiesVisited++;

            currentCityIdx = nextCityIdx;
            candidateCities = null;
        }

        //=============================================================
        //Going back to start
        //=============================================================
        tourCityIdx.add(startCityIdx);
        totalDistanceTravelled +=  Main.calculateDistance(currentCityIdx, startCityIdx);
        numberOfRoadsTravelled++;

        constructionDuration = System.currentTimeMillis() - startTime;


        if(!checkSolution()){
            System.out.println("******WRONG CONSTRUCTION******");
            printConstruction();
            Main.constructionWrongSolution++;
            //exit(0);
        }

        visited = null;

        System.out.println("Finished Construction in Nearest Neighbor Heuristic");
        System.out.println();
    }

    @Override
    void improve() {
        //doing nothing here
    }

}

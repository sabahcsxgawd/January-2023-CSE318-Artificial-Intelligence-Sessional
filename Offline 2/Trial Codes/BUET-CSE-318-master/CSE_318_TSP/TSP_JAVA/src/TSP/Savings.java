package TSP;

import javafx.util.Pair;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedList;

class Savings extends Solution{
    private ArrayList<ArrayList<Integer>> adjacencyList;
    private ArrayList <Pair<Pair<Integer, Integer>, Float>> savings;

    private long startTime;

    Savings() {
        super();

        if (Main.RANDOMIZED_START){
            startCityIdx =  Main.rand.nextInt(Main.n);
        }
        else{
            startCityIdx = Main.startCity;
        }

        System.out.println("Starting City: " + (startCityIdx+1) );

        adjacencyList = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < Main.n; i++) {
            adjacencyList.add(new ArrayList<Integer>());
        }

        savings = new ArrayList <Pair<Pair<Integer, Integer>, Float>>(); //((i,j),saving)

    }

    private void calculateSavings(){
        //=============================================================
        //Calculating Savings
        //=============================================================
        System.out.println("Started Calculating Savings");

        savings.clear();
        for (int i = 0; i < Main.n; i++) {
            if(i==startCityIdx){
                continue;
            }
            float distIK = Main.calculateDistance(i, startCityIdx);
            for (int j = i+1; j < Main.n; j++) {
                if (j==startCityIdx || i==j){
                    continue;
                }
                float distJK = Main.calculateDistance(j, startCityIdx);
                float distIJ = Main.calculateDistance(i, j);
                float save = distIK + distJK - distIJ;
                savings.add(new Pair<>(new Pair<>(i,j), save));
            }
        }
        System.out.println("Finished Calculating Savings");


        //=============================================================
        //Sorting Savings
        //=============================================================
        System.out.println("Started Sorting Savings");
        savings.sort(new Comparator<Pair<Pair<Integer, Integer>, Float>>() {
            @Override
            public int compare(Pair<Pair<Integer, Integer>, Float> o2, Pair<Pair<Integer, Integer>, Float> o1) {
                return Float.compare(o1.getValue(), o2.getValue()) ;
            }
        });
        System.out.println("Finished Sorting Savings");


        //=============================================================
        //Printing Sorted Savings
        //=============================================================
//        for (Pair<Pair<Integer, Integer>, Float> entry: savings) {
//            System.out.println( entry.getKey().getKey() + " " +  entry.getKey().getValue() + " " + entry.getValue());
//        }
    }

    private void initializeAdjacencyList(){
        //=============================================================
        //Connecting Every Node with Starting Node
        //=============================================================
        for (int i = 0; i < Main.n; i++) {
            if(i==startCityIdx){
                continue;
            }
            ///considering each edge bidirectional for implementation purpose
            adjacencyList.get(startCityIdx).add(i);
            adjacencyList.get(i).add(startCityIdx);

            //2nd edge
            adjacencyList.get(i).add(startCityIdx);
            adjacencyList.get(startCityIdx).add(i);

        }

//        System.out.println("Printing Initial Adjacency Lists");
//        printAdjacencyList();
    }

    private void updateAdjacencyList(){
        //=============================================================
        //Updating Adjacency Lists According to Savings
        //=============================================================

        System.out.println("Iterating Sorted Savings Array to Update Adjacency Lists");
        while (!savings.isEmpty() && adjacencyList.get(startCityIdx).size()>2) {
            int removeIdx = Main.rand.nextInt(Main.USE_CANDIDATES);

            if(removeIdx>=savings.size()){
                removeIdx = savings.size()-1;
            }
            //System.out.println("REMOVEIDX HERE : " + removeIdx);



            Pair<Pair<Integer, Integer>, Float> entry = savings.remove(removeIdx);
            int i = entry.getKey().getKey();
            int j = entry.getKey().getValue();
//            System.out.println();
//            System.out.println(i + " " + j);

            if(!adjacencyList.get(startCityIdx).contains(i) || !adjacencyList.get(startCityIdx).contains(j)){
                //System.out.println("Not enough edges to remove");
                continue;
            }

            updateGraph(i, j);

            if(!checkReachable(i) ||!checkReachable(i)){
                revertGraph(i, j);
            }

//            System.out.println("Printing Changed Adjacency Lists for " + i + " " + j);
//            printAdjacencyList();

        }

//        System.out.println("Printing Updated Adjacency Lists");
//        printAdjacencyList();

    }

    private boolean checkReachable(int checkCity){  //running bfs search
        LinkedList <Integer> queue = new LinkedList<Integer>();

        boolean [] enqueued = new boolean[Main.n];
        for (int i = 0; i < Main.n; i++) {
            enqueued[i] = false;
        }

        queue.add(startCityIdx);
        enqueued[startCityIdx] = true;

        while (!queue.isEmpty()){
            int u = queue.removeFirst();
            for (int v : adjacencyList.get(u)) {
                if(v==checkCity){
                    queue = null;
                    enqueued = null;
                    return true;
                }
                if(!enqueued[v]){
                    queue.add(v);
                    enqueued[v] = true;
                }
            }
        }

        queue = null;
        enqueued = null;
        return false;
    }

    private void updateGraph(int i, int j){
        //removing 2 bidirectional edges
        adjacencyList.get(i).remove(new Integer(startCityIdx));
        adjacencyList.get(startCityIdx).remove(new Integer(i));

        adjacencyList.get(startCityIdx).remove(new Integer(j));
        adjacencyList.get(j).remove(new Integer(startCityIdx));

        //add bidirectional edge between i and j
        adjacencyList.get(i).add(j);
        adjacencyList.get(j).add(i);
    }


    private void revertGraph(int i, int j){
        adjacencyList.get(i).add(startCityIdx);
        adjacencyList.get(startCityIdx).add(i);

        adjacencyList.get(startCityIdx).add(j);
        adjacencyList.get(j).add(startCityIdx);

        //remove bidirectional edge between i and j
        adjacencyList.get(i).remove(new Integer(j));
        adjacencyList.get(j).remove(new Integer(i));


    }


    private void buildTourArray(){
        tourCityIdx.add(startCityIdx);
        int currentCityIdx = startCityIdx;

        while (tourCityIdx.size()!=Main.n){
            ArrayList<Integer> list = adjacencyList.get(currentCityIdx);

            int nextCityIdx = list.get(0);
            if(tourCityIdx.contains(nextCityIdx)){
                nextCityIdx = list.get(1);
            }

            tourCityIdx.add(nextCityIdx);
            totalDistanceTravelled += Main.calculateDistance(currentCityIdx, nextCityIdx);
            numberOfRoadsTravelled++;

            currentCityIdx = nextCityIdx;

        }

        //going back to start city
        tourCityIdx.add(startCityIdx);
        totalDistanceTravelled +=  Main.calculateDistance(currentCityIdx, startCityIdx);
        numberOfRoadsTravelled++;
    }

    private void printAdjacencyList(){
        for (int n1 = 0; n1 < Main.n; n1++) {
            System.out.print((n1+1) + ": ");
            for (int n2: adjacencyList.get(n1) ) {
                System.out.print((n2+1) + " ");
            }
            System.out.println();
        }

    }



    @Override
    void construct() {
        System.out.println("Starting Construction in Savings Heuristic");
        startTime = System.currentTimeMillis();

        calculateSavings();

        initializeAdjacencyList();

        updateAdjacencyList();

        buildTourArray();

        if(!checkSolution()){
            System.out.println("******WRONG CONSTRUCTION******");
            printConstruction();
            Main.constructionWrongSolution++;
            //exit(0);
        }

        constructionDuration = System.currentTimeMillis() - startTime;

        adjacencyList = null;
        savings = null;

        System.out.println("Finished Construction in Savings Heuristic");
        System.out.println();

        //printConstruction();
    }

    @Override
    void improve() {
        //doing nothing here
    }

}

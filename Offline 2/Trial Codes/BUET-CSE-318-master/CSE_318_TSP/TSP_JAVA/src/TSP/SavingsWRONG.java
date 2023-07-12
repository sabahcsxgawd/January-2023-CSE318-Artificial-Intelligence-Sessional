//package TSP;
//
//import javafx.util.Pair;
//
//import java.util.ArrayList;
//import java.util.Comparator;
//
//
//public class Savings2 extends Solution{
//    int []nextCity;
//
//    long startTime;
//
//    int numberOfCitiesVisited;
//
//    public Savings2() {
//        super();
//
//        if (Main.RANDOMIZED_START){
//            startCityIdx =  Main.rand.nextInt(Main.n);
//        }
//        else{
//            startCityIdx = 0;
//        }
//
//        System.out.println("Starting City: " + startCityIdx);
//
//        numberOfCitiesVisited = 0;
////        tourCityIdx.add(startCityIdx);
////        numberOfCitiesVisited = 1;  //start city is visited
//
//        nextCity = new int[Main.n];
//        for (int i = 0; i < Main.n; i++) {
//            nextCity[i] = -1;
//        }
//
//    }
//
//    @Override
//    void construct() {
//        System.out.println("Starting Construction in Savings Heuristic");
//        startTime = System.currentTimeMillis();
//
//        System.out.println("Started Calculating Savings");
//                    //((i,j),saving)
//        ArrayList <Pair<Pair<Integer, Integer>, Float>> savings = new ArrayList <Pair<Pair<Integer, Integer>, Float>>();
//
//        for (int i = 0; i < Main.n; i++) {
//            if(i==startCityIdx){
//                continue;
//            }
//
//            float distIK = Main.calculateDistance(i, startCityIdx);
//
//            for (int j = i+1; j < Main.n; j++) {
//                if (j==startCityIdx || i==j){
//                    continue;
//                }
//
//                float distJK = Main.calculateDistance(j, startCityIdx);
//                float distIJ = Main.calculateDistance(i, j);
//
//                float save = distIK + distJK - distIJ;
//
//                savings.add(new Pair<>(new Pair<>(i,j), save));
//
//            }
//        }
//        System.out.println("Finished Calculating Savings");
//
//        System.out.println("Started Sorting Savings");
//        savings.sort(new Comparator<Pair<Pair<Integer, Integer>, Float>>() {
//            @Override
//            public int compare(Pair<Pair<Integer, Integer>, Float> o2, Pair<Pair<Integer, Integer>, Float> o1) {
//                return Float.compare(o1.getValue(), o2.getValue()) ;
//            }
//        });
//        System.out.println("Finished Sorting Savings");
//
//        for (Pair<Pair<Integer, Integer>, Float> entry: savings) {
//            System.out.println( entry.getKey().getKey() + " " +  entry.getKey().getValue() + " " + entry.getValue());
//        }
//
//        if (!savings.isEmpty()){
//            nextCity[startCityIdx] = savings.get(0).getKey().getKey();
//            numberOfCitiesVisited++;
//        }
//
//        System.out.println("Iterating Sorted Savings Array to Populate nextCity Array");
//        for (Pair<Pair<Integer, Integer>, Float> entry: savings) {
//            int i = entry.getKey().getKey();
//            int j = entry.getKey().getValue();
//            if(nextCity[i] != -1 || nextCity[j]==i){
//                continue;
//            }
//            if(numberOfCitiesVisited == Main.n){
//                break;
//            }
//
//            System.out.println(i + " " + j);
//            nextCity[i] = j;
//            numberOfCitiesVisited++;
//        }
//
//        System.out.println("Printing nextCity array");
//        for (int i = 0; i < Main.n; i++) {
//            System.out.println(i + " " + nextCity[i]);
//        }
//
//        for (int i = startCityIdx; nextCity[i] != -1; i = nextCity[i]) {
//            tourCityIdx.add(i);
//            totalDistanceTravelled += Main.calculateDistance(i, nextCity[i]);
//            numberOfRoadsTravelled++;
//        }
//
//        //going back to start city
//        tourCityIdx.add(startCityIdx);
//        totalDistanceTravelled +=  Main.calculateDistance(tourCityIdx.get(tourCityIdx.size()-2), startCityIdx);
//        numberOfRoadsTravelled++;
//
//        constructionDuration = System.currentTimeMillis() - startTime;
//
//        System.out.println("Finished Construction in Savings Heuristic");
//        System.out.println();
//
//    }
//
//    @Override
//    void improve() {
//        //doing nothing here
//    }
//
//}

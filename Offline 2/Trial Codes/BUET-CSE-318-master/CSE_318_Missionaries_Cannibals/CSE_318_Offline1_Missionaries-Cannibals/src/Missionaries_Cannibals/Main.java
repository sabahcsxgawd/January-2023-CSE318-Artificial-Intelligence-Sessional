package Missionaries_Cannibals;

//Assuming m missionaries and c cannibals are initially at the left side of the river
//Boat has capacity cap

import java.util.Scanner;

public class Main {

    public static final int TIMEOUT_SECONDS = 30;
    public static final int MAX_ITERATIONS = 1000000;

    public static int m;
    public static int c;
    public static int cap;

    public static void main(String[] args) {
        //System.out.println("Hello World!");

        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the number of Missionaries, Cannibals and capacity of the boat:");

        m = sc.nextInt();
        c = sc.nextInt();
        cap = sc.nextInt();

        Node bfs_Result = new BFS_Implementation().runBFS();

        Node dfs_Result = new DFS_Implementation().runDFS();

        if(bfs_Result == null){
            System.out.println("BFS Failed");
        }
        else {
            System.out.println();
            System.out.println("Printing path in BFS...");
            bfs_Result.printPath();
            System.out.println();
        }

        if(dfs_Result == null){
            System.out.println("DFS Failed");
        }
        else{
            System.out.println();
            System.out.println("Printing path in DFS...");
            dfs_Result.printPath();
            System.out.println();
        }



    }


}

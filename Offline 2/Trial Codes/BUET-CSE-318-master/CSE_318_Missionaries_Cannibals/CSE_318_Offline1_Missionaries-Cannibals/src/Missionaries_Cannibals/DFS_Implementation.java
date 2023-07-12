package Missionaries_Cannibals;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;

public class DFS_Implementation {
    private HashMap<Node,Boolean> nodeMap = new HashMap <Node,Boolean>(); //Boolean value corresponds to isExplored
    private LinkedList<Node> nodeStack = new LinkedList <Node>(); //DFS Stack. addFirst(E e) and removeFirst() will be used as push and pop
    private long iteration;
    private long MAX_TIME;
    public DFS_Implementation() {
        iteration = 0;

        MAX_TIME = System.currentTimeMillis() + Main.TIMEOUT_SECONDS*1000;


    }

    public Node runDFS(){

        Node initialNode = new Node(Main.m, Main.c, true, null, 0);

        nodeMap.put(initialNode, false);
        nodeStack.addFirst(initialNode);

        while (!nodeStack.isEmpty()){
            iteration++;

            Node u = nodeStack.removeFirst();
            nodeMap.replace(u, true); //explored



            //checking maximum iteration constraint
            if(iteration > Main.MAX_ITERATIONS){
                System.out.println("Maximum iterations reached in DFS. Terminating...");
                return null;
            }

            //checking timeout constraint
            if(System.currentTimeMillis() > MAX_TIME){
                System.out.println("Timeout reached in DFS. Terminating...");
                return null;
            }


            ArrayList <Node> childNodes = u.generateChildNodes();

            for (Node v: childNodes) {

                if(v.isGoal()){

                    System.out.println();
                    System.out.println("***DFS RESULT***");
                    System.out.println("Number of Expanded Nodes in DFS = " + iteration);
                    System.out.println("Number of Explored Nodes in DFS = " + nodeMap.size());
                    System.out.println("Number of Steps required in DFS = " + v.distance);
                    System.out.println("Time required in DFS = " + ( ( System.currentTimeMillis() - MAX_TIME + Main.TIMEOUT_SECONDS*1000 ) ) + " ms");

//                System.out.println();
//                System.out.println("Printing path in DFS...");
//                u.printPath();
//                System.out.println();
                    return u;
                }

                //System.out.println("Child" + v);
                if (!nodeMap.containsKey(v)){
                    nodeMap.put(v, false);
                    nodeStack.addFirst(v);
                }
//                else {
//                    System.out.println("HashMap already contains : " + v);
//                }

            }

        }

        //no path found from initial node to goal node
        System.out.println("Solution not found in DFS");
        return null;
    }


}

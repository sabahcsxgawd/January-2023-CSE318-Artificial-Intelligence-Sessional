package N_Puzzle;

import javafx.util.Pair;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;

public class Node {
    private int array[][];
    private int dist;
    private int heuristicVal;
    private String msg;
    private Node parent;
    private Pair<Integer, Integer> spacePosition;

    public Node(int[][] array, int dist, int heuristicVal, String msg, Node parent, Pair<Integer, Integer> sp) {
        this.array = SupportingFunctions.copyArray(array);
        this.dist = dist;
        this.heuristicVal = heuristicVal;
        this.msg = msg;
        this.parent = parent;
        this.spacePosition = sp;
    }

    public int[][] getArray() {
        return SupportingFunctions.copyArray(array);
    }

    public void setArray(int[][] array) {
        this.array = SupportingFunctions.copyArray(array);
    }

    public int getDist() {
        return dist;
    }

    public void setDist(int dist) {
        this.dist = dist;
    }

    public int getHeuristicVal() {
        return heuristicVal;
    }

    public void setHeuristicVal(int heuristicVal) {
        this.heuristicVal = heuristicVal;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public Node getParent() {
        return parent;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public Pair<Integer, Integer> getSpacePosition() {
        return spacePosition;
    }

    public void setSpacePosition(Pair<Integer, Integer> spacePosition) {
        this.spacePosition = spacePosition;
    }

    @Override
    public String toString() {
        return "Node{" +
                "array=" + Arrays.toString(array) +
                ", dist=" + dist +
                ", heuristicVal=" + heuristicVal +
                ", msg='" + msg + '\'' +
                ", parent=" + parent +
                ", spacePosition=" + spacePosition +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Node node = (Node) o;

        for(int i=0; i<Main.k; i++){
            for (int j=0; j<Main.k; j++) {
                if(array[i][j] != node.array[i][j])
                    return false;
            }
        }
        return true;

        //return Arrays.equals(array, node.getArray());

    }

    @Override
    public int hashCode() {
        int hash = 0;
        for(int i=0; i<Main.k; i++){
            for (int j=0; j<Main.k; j++) {
                hash+= (i+1)*(j+1)*Objects.hash(array[i][j]);
            }
        }

        return hash;

        //return Arrays.hashCode(array);
    }

    ArrayList <Node> getChildrenHamming(){
        ArrayList <Node> children = new ArrayList<Node>();

        int i = spacePosition.getKey();
        int j = spacePosition.getValue();

        //1st case: sth down
        if(i>0){
            int val = array[i-1][j];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i-1,j));
            //int childArr[][] = SupportingFunctions.swap(array, i,j, i-1,j);

            Node child = new Node(childArr, dist+1, SupportingFunctions.getHammingDistance(childArr), val + " DOWN", this, new Pair<Integer, Integer>(i-1,j));

            children.add(child);
        }

        //2nd case: sth up
        if(i<Main.k-1){
            int val = array[i+1][j];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i+1,j));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getHammingDistance(childArr), val + " UP", this, new Pair<Integer, Integer>(i+1,j));

            children.add(child);
        }

        //3rd case: sth right
        if(j>0){
            int val = array[i][j-1];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i,j-1));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getHammingDistance(childArr), val + " RIGHT", this, new Pair<Integer, Integer>(i,j-1));

            children.add(child);
        }

        //4t case: sth left
        if(j<Main.k-1){
            int val = array[i][j+1];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i,j+1));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getHammingDistance(childArr), val + " LEFT", this, new Pair<Integer, Integer>(i,j+1));

            children.add(child);
        }






        return children;
    }

    ArrayList <Node> getChildrenManhattan(){

        ArrayList <Node> children = new ArrayList<Node>();

        int i = spacePosition.getKey();
        int j = spacePosition.getValue();

        //1st case: sth down
        if(i>0){
            int val = array[i-1][j];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i-1,j));
            //int childArr[][] = SupportingFunctions.swap(array, i,j, i-1,j);

            Node child = new Node(childArr, dist+1, SupportingFunctions.getManhattanDistance(childArr), val + " DOWN", this, new Pair<Integer, Integer>(i-1,j));
            //child.printNode();
            children.add(child);
        }

        //2nd case: sth up
        if(i<Main.k-1){
            int val = array[i+1][j];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i+1,j));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getManhattanDistance(childArr), val + " UP", this, new Pair<Integer, Integer>(i+1,j));
            //child.printNode();
            children.add(child);
        }

        //3rd case: sth right
        if(j>0){
            int val = array[i][j-1];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i,j-1));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getManhattanDistance(childArr), val + " RIGHT", this, new Pair<Integer, Integer>(i,j-1));
            //child.printNode();
            children.add(child);
        }

        //4t case: sth left
        if(j<Main.k-1){
            int val = array[i][j+1];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i,j+1));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getManhattanDistance(childArr), val + " LEFT", this, new Pair<Integer, Integer>(i,j+1));
            //child.printNode();
            children.add(child);
        }






        return children;
    }

    ArrayList <Node> getChildrenLinear(){
        ArrayList <Node> children = new ArrayList<Node>();

        int i = spacePosition.getKey();
        int j = spacePosition.getValue();

        //1st case: sth down
        if(i>0){
            int val = array[i-1][j];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i-1,j));
            //int childArr[][] = SupportingFunctions.swap(array, i,j, i-1,j);

            Node child = new Node(childArr, dist+1, SupportingFunctions.getLinearConflicts(childArr), val + " DOWN", this, new Pair<Integer, Integer>(i-1,j));

            children.add(child);
        }

        //2nd case: sth up
        if(i<Main.k-1){
            int val = array[i+1][j];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i+1,j));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getLinearConflicts(childArr), val + " UP", this, new Pair<Integer, Integer>(i+1,j));

            children.add(child);
        }

        //3rd case: sth right
        if(j>0){
            int val = array[i][j-1];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i,j-1));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getLinearConflicts(childArr), val + " RIGHT", this, new Pair<Integer, Integer>(i,j-1));

            children.add(child);
        }

        //4t case: sth left
        if(j<Main.k-1){
            int val = array[i][j+1];
            int childArr[][] = SupportingFunctions.swap(array, new Pair<Integer, Integer>(i,j), new Pair<Integer, Integer>(i,j+1));

            Node child = new Node(childArr, dist+1, SupportingFunctions.getLinearConflicts(childArr), val + " LEFT", this, new Pair<Integer, Integer>(i,j+1));

            children.add(child);
        }


        return children;
    }

    public void printNode(){
        System.out.println(msg);
        System.out.println("dist = "+dist+", heuristicVal = "+heuristicVal+", Space position = (" + spacePosition.getKey()+","+spacePosition.getValue()+")" );

        //System.out.println(node.getSpacePosition().getKey() + " " + node.getSpacePosition().getValue());
        for(int i=0; i<Main.k; i++){
            for (int j=0; j<Main.k; j++) {

                if(array[i][j]==Main.SPACE){
                    System.out.printf("  ");
                }
                else {
                    System.out.printf("%d ", array[i][j]);
                }

            }
            System.out.println();

        }
        System.out.println();
    }

    public void printSteps(){
        if(parent!=null)
            parent.printSteps();
        printNode();
    }

    public boolean isGoal(){
        if(SupportingFunctions.getHammingDistance(array)==0){
            return true;
        }
        else {
            return false;
        }
    }

    public int getEffectiveVal(){
        return dist+heuristicVal;
    }

}

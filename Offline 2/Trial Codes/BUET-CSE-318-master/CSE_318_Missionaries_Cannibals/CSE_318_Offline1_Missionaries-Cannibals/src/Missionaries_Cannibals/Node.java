package Missionaries_Cannibals;

import java.util.ArrayList;
import java.util.Objects;

public class Node {
    int left_m;
    int left_c;
    boolean boatInLeftSide;
    int distance;

    Node parent;

    public Node(int left_m, int left_c, boolean boatInLeftSide, Node par, int d) {
        this.left_m = left_m;
        this.left_c = left_c;
        this.boatInLeftSide = boatInLeftSide;

        parent = par;
        distance = d;

    }

    public int getLeft_m() {
        return left_m;
    }

    public void setLeft_m(int left_m) {
        this.left_m = left_m;
    }

    public int getLeft_c() {
        return left_c;
    }

    public void setLeft_c(int left_c) {
        this.left_c = left_c;
    }

    public boolean isBoatInLeftSide() {
        return boatInLeftSide;
    }

    public void setBoatInLeftSide(boolean boatInLeftSide) {
        this.boatInLeftSide = boatInLeftSide;
    }

    @Override
    public boolean equals(Object o) {   //p not considered
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Node node = (Node) o;
        return left_m == node.left_m &&
                left_c == node.left_c &&
                boatInLeftSide == node.boatInLeftSide;
    }

    @Override
    public int hashCode() {
        return Objects.hash(left_m, left_c, boatInLeftSide); //p not considered
    }

    @Override
    public String toString() {  //remaining
        return "Node{" +
                "left_m=" + left_m +
                ", left_c=" + left_c +
                ", boatInLeftSide=" + boatInLeftSide +
                '}';
    }

    boolean isGoal(){
        return ( left_m == 0 && left_c ==0 ) ;
    }

    boolean isValid(){
        if(left_m <= Main.m && left_c <= Main.c && left_m>=0 && left_c>=0 && ( left_m >= left_c  || left_m==0) && ( (Main.m-left_m) >= (Main.c-left_c) || (Main.m-left_m)==0 ) )
            return true;
        else
            return false;
    }

    ArrayList <Node> generateChildNodes(){  //remaining
        //System.out.println("In generateChildNodes");
        ArrayList <Node> children = new ArrayList <Node>();

        for(int i=1; i<=Main.cap; i++){ //i denotes how many passengers

            //System.out.println("In outer loop with i=" + i);

            for(int j=0; j<=i; j++ ){   //j denotes missionaries carried by boat
                //j missionaries and (i-j) cannibals carried by boat

                //System.out.println("In inner loop with j=" + j);

                Node newNode = null;

                if(boatInLeftSide){ //carry passengers to right side
                    newNode = new Node(left_m-j, left_c - (i-j), !boatInLeftSide, this, distance+1);
                    if(newNode.isValid()){
                        children.add(newNode);
                    }
                }
                else{ //carry passengers to left side
                    newNode = new Node(left_m + j, left_c + (i-j), !boatInLeftSide, this, distance+1);
                    if(newNode.isValid()){
                        children.add(newNode);
                    }
                }

            }

        }

//        for (Node n: children) {
//            System.out.println("In generateChildNodes(), Child: " + n);
//        }

        return children;
    }

    void printPath(){
        if(parent!=null){
            parent.printPath();
        }

        System.out.println(this);

    }


}

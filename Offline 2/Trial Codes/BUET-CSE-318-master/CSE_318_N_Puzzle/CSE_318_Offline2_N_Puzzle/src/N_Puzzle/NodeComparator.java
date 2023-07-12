package N_Puzzle;

import java.util.Comparator;

public class NodeComparator implements Comparator<Node> {
    @Override
    public int compare(Node o1, Node o2) {

        if(o1.getDist()+o1.getHeuristicVal() > o2.getDist()+o2.getHeuristicVal())
            return 1;
        else
            return -1;

    }
}

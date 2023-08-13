#include <bits/stdc++.h>
using namespace std;

#define ll long long

class Graph {

private:
    int vertexCount, edgeCount;
    ll minWeightedEdge, maxWeightedEdge;
    vector<map<int, int>> weights;

public:
    Graph() = delete;

    Graph(const Graph &) = delete;

    Graph(int vertexCount, int edgeCount) {
        this->vertexCount = vertexCount;
        this->edgeCount = edgeCount;    
        this->minWeightedEdge = LLONG_MAX;
        this->maxWeightedEdge = LLONG_MIN;
        this->weights.resize(this->vertexCount + 1);
    }

    void addEdge(int u, int v, ll w) {
        weights[u][v] = w;
        this->minWeightedEdge = min(this->minWeightedEdge, w);
        this->maxWeightedEdge = max(this->maxWeightedEdge, w);
    }

    ll getWeight(int u, int v) {
        return this->weights[u][v];
    }

    ll getMaxWeightedEdege() {
        return this->maxWeightedEdge;
    }

    ll getMinWeightedEdege() {
        return this->minWeightedEdge;
    }

};



int main(int argc, char* argv[]) {

    int n, m, u, v;
    ll w;
    cin >> n >> m;

    Graph *g = new Graph(n, m);

    for(int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g->addEdge(u, v, w);
    }

    cout << g->getMinWeightedEdege() << ' ' << g->getMaxWeightedEdege() << '\n';

    delete g;

    return 0;
}
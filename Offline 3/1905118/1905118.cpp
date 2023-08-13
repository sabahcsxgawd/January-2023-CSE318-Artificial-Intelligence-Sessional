#include <bits/stdc++.h>
using namespace std;

#define ll long long

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dist(0.0, 1.0);

class Graph
{

private:
    int nodeCount, edgeCount;
    ll minWeightedEdge, maxWeightedEdge;
    vector<map<int, int>> weights;
    vector<pair<int, int>> edges;

public:
    Graph() = delete;

    Graph(const Graph &) = delete;

    Graph(int nodeCount, int edgeCount)
    {
        this->nodeCount = nodeCount;
        this->edgeCount = edgeCount;
        this->minWeightedEdge = LLONG_MAX;
        this->maxWeightedEdge = LLONG_MIN;
        this->weights.resize(this->nodeCount + 1);
    }

    void addEdge(int u, int v, ll w)
    {
        this->weights[u][v] = w;
        this->weights[v][u] = w;
        this->minWeightedEdge = min(this->minWeightedEdge, w);
        this->maxWeightedEdge = max(this->maxWeightedEdge, w);
        this->edges.push_back(make_pair(u, v));
    }

    int getNodeCount()
    {
        return this->nodeCount;
    }

    int getEdgeCount()
    {
        return this->edgeCount;
    }

    ll getWeight(int u, int v)
    {
        return this->weights[u][v];
    }

    ll getMaxWeightedEdege()
    {
        return this->maxWeightedEdge;
    }

    ll getMinWeightedEdege()
    {
        return this->minWeightedEdge;
    }

    ll getSigmaX(int v, const set<int> &Y)
    {
        ll sigmaX = 0;

        for (int u : Y)
        {
            sigmaX += this->weights[v][u];
        }

        return sigmaX;
    }

    ll getSigmaY(int v, const set<int> &X)
    {
        ll sigmaY = 0;

        for (int u : X)
        {
            sigmaY += this->weights[v][u];
        }

        return sigmaY;
    }

    ll getMaxCutWeight(const set<int> &X, const set<int> &Y)
    {
        ll maxCutWeight = 0;

        for (int i : X)
        {
            for (int j : Y)
            {
                maxCutWeight += this->weights[i][j];
            }
        }

        return maxCutWeight;
    }

    vector<pair<int, int>> &getEdges()
    {
        return this->edges;
    }
};

class MaxCut
{

private:
    Graph *g;
    set<int> SEMI_GREEDY_S, SEMI_GREEDY_S_bar;

public:
    MaxCut() = delete;

    MaxCut(const MaxCut &) = delete;

    MaxCut(Graph *g)
    {
        this->g = g;
    }

    ll SEMI_GREEDY_MAXCUT()
    {
        double alpha = dist(gen);
        ll wMin = this->g->getMinWeightedEdege(), wMax = this->g->getMaxWeightedEdege();
        double miu = this->g->getMinWeightedEdege() + (alpha * (this->g->getMaxWeightedEdege() - this->g->getMinWeightedEdege()));
        vector<pair<int, int>> edges = this->g->getEdges();
        vector<pair<int, int>> edgesRCL;
        for (pair<int, int> p : edges)
        {
            if (g->getWeight(p.first, p.second) >= miu)
            {
                edgesRCL.push_back(p);
            }
        }
        uniform_int_distribution<> randomPickDist(0, edgesRCL.size() - 1);
        pair<int, int> randomEdge = edgesRCL[randomPickDist(gen)];
        this->SEMI_GREEDY_S.clear();
        this->SEMI_GREEDY_S_bar.clear();
        this->SEMI_GREEDY_S.insert(randomEdge.first);
        this->SEMI_GREEDY_S_bar.insert(randomEdge.second);
        int nodeCount = this->g->getNodeCount();
        set<int> nodeTracker;
        for (int i = 1; i <= nodeCount; i++)
        {
            nodeTracker.insert(i);
        }
        nodeTracker.erase(randomEdge.first);
        nodeTracker.erase(randomEdge.second);

        vector<int> nodesRCL;

        while (nodeTracker.size())
        {
            ll minSigmaX, minSigmaY, maxSigmaX, maxSigmaY;
            minSigmaX = minSigmaY = LLONG_MAX;
            maxSigmaX = maxSigmaY = LLONG_MIN;

            for (auto it = nodeTracker.begin(); it != nodeTracker.end(); it++)
            {
                minSigmaX = min(minSigmaX, this->g->getSigmaX(*it, this->SEMI_GREEDY_S_bar));
                minSigmaY = min(minSigmaY, this->g->getSigmaY(*it, this->SEMI_GREEDY_S));
                maxSigmaX = max(maxSigmaX, this->g->getSigmaX(*it, this->SEMI_GREEDY_S_bar));
                maxSigmaY = max(maxSigmaY, this->g->getSigmaY(*it, this->SEMI_GREEDY_S));
            }

            wMin = min(minSigmaX, minSigmaY);
            wMax = max(maxSigmaX, maxSigmaY);

            miu = wMin + (alpha * (wMax - wMin));
            nodesRCL.clear();

            for (auto it = nodeTracker.begin(); it != nodeTracker.end(); it++)
            {
                if (max(this->g->getSigmaX(*it, this->SEMI_GREEDY_S_bar), this->g->getSigmaY(*it, this->SEMI_GREEDY_S)) >= miu)
                {
                    nodesRCL.push_back(*it);
                }
            }

            assert(nodesRCL.size() > 0);

            uniform_int_distribution<> randomIntPickDist(0, nodesRCL.size() - 1);

            int randomNode = nodesRCL[randomIntPickDist(gen)];

            if (this->g->getSigmaX(randomNode, this->SEMI_GREEDY_S_bar) > this->g->getSigmaY(randomNode, this->SEMI_GREEDY_S))
            {
                nodeTracker.erase(randomNode);
                this->SEMI_GREEDY_S.insert(randomNode);
            }
            else
            {
                nodeTracker.erase(randomNode);
                this->SEMI_GREEDY_S_bar.insert(randomNode);
            }
        }

        return this->g->getMaxCutWeight(this->SEMI_GREEDY_S, this->SEMI_GREEDY_S_bar);
    }

    ll LOCAL_SEARCH_MAXCUT() {
        bool change = true;

        while(change) {
            change = false;
            for(int i = 1; (i <= g->getNodeCount()) && !change; i++) {
                if(this->SEMI_GREEDY_S.find(i) != this->SEMI_GREEDY_S.end()) {
                    if(this->g->getSigmaY(i, this->SEMI_GREEDY_S) > this->g->getSigmaX(i, this->SEMI_GREEDY_S_bar)) {
                        change = true;
                        this->SEMI_GREEDY_S_bar.insert(i);
                        this->SEMI_GREEDY_S.erase(i);
                    }
                }
                else {
                    if(this->g->getSigmaX(i, this->SEMI_GREEDY_S_bar) > this->g->getSigmaY(i, this->SEMI_GREEDY_S)) {
                        change = true;
                        this->SEMI_GREEDY_S.insert(i);
                        this->SEMI_GREEDY_S_bar.erase(i);
                    }
                }
            }
        }

        return this->g->getMaxCutWeight(this->SEMI_GREEDY_S, this->SEMI_GREEDY_S_bar);
    }
};

int main(int argc, char *argv[])
{

    int n, m, u, v;
    ll w;
    cin >> n >> m;

    Graph *g = new Graph(n, m);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g->addEdge(u, v, w);
    }

    MaxCut semi_greedy_solver(g);

    cout << semi_greedy_solver.SEMI_GREEDY_MAXCUT() << '\n';
    cout << semi_greedy_solver.LOCAL_SEARCH_MAXCUT() << '\n';

    delete g;

    return 0;
}
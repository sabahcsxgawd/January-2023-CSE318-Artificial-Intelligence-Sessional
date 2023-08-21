#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pss pair<set<int>, set<int>>
#define pwpss pair<ll, pss>

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dist(0.0, 1.0);
uniform_int_distribution<> coin(0, 1);

map<int, string> bestKnownBound;

class Graph
{

private:
    int nodeCount, edgeCount;
    ll minWeightedEdge, maxWeightedEdge;
    pair<int, int> maxEdge;
    vector<map<int, ll>> weights;
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
        this->edges.reserve(edgeCount);
    }

    void addEdge(int u, int v, ll w)
    {
        if (this->weights[u].find(v) == this->weights[u].end())
        {
            this->weights[v][u] = this->weights[u][v] = w;
            this->edges.emplace_back(make_pair(u, v));
        }
        else
        {
            this->weights[v][u] = this->weights[u][v] = max(w, this->weights[u][v]);
        }
        this->minWeightedEdge = min(this->minWeightedEdge, w);
        this->maxWeightedEdge = max(this->maxWeightedEdge, w);
        if (w == this->maxWeightedEdge)
        {
            this->maxEdge = make_pair(u, v);
        }
    }

    pair<int, int> getMaxEdge()
    {
        return this->maxEdge;
    }

    map<int, ll> getAdjListWeights(int i)
    {
        return this->weights[i];
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
        if (this->weights[u].find(v) == this->weights[u].end())
        {
            return 0;
        }
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
            sigmaX += this->getWeight(v, u);
        }

        return sigmaX;
    }

    ll getSigmaY(int v, const set<int> &X)
    {
        ll sigmaY = 0;

        for (int u : X)
        {
            sigmaY += this->getWeight(v, u);
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
                maxCutWeight += this->getWeight(i, j);
            }
        }

        return maxCutWeight;
    }

    vector<pair<int, int>> getEdges()
    {
        return this->edges;
    }
};

class MaxCut
{

private:
    Graph *g;
    set<int> member_S, member_S_bar;
    vector<tuple<int, ll, ll>> sigmas;
    ll LOCAL_ITER_CNT, GREEDY_W, GREEDY_LOCAL_W, SEMI_GREEDY_CUM_W, RAND_CUM_W, LOCAL_CUM_W;

public:
    MaxCut() = delete;

    MaxCut(const MaxCut &) = delete;

    MaxCut(Graph *g)
    {
        this->g = g;
        this->SEMI_GREEDY_CUM_W = this->RAND_CUM_W = 0;
        this->sigmas.resize(g->getNodeCount() + 1, make_tuple(0, 0, 0));
        this->LOCAL_ITER_CNT = 1;
        this->GREEDY_W = this->GREEDY_MAXCUT();
        pss tempu = make_pair(this->member_S, this->member_S_bar);
        this->GREEDY_LOCAL_W = this->LOCAL_SEARCH_MAXCUT(tempu, this->GREEDY_W).first;
    }

    ll GREEDY_MAXCUT()
    {
        this->member_S.clear();
        this->member_S_bar.clear();
        int nodeCount = this->g->getNodeCount();
        pair<int, int> maxEdge = this->g->getMaxEdge();
        map<int, ll> tempMap;
        ll tempW = 0;
        for (int i = 1; i <= nodeCount; i++)
        {
            get<0>(this->sigmas[i]) = 0;
            get<1>(this->sigmas[i]) = 0;
            get<2>(this->sigmas[i]) = 0;
        }

        this->member_S.emplace(maxEdge.first);
        get<0>(this->sigmas[maxEdge.first]) = 1;
        this->member_S_bar.emplace(maxEdge.second);
        get<0>(this->sigmas[maxEdge.second]) = 2;
        tempW += this->g->getWeight(maxEdge.first, maxEdge.second);

        tempMap = this->g->getAdjListWeights(maxEdge.first);

        for (auto it : tempMap)
        {
            get<2>(this->sigmas[it.first]) += it.second;
        }

        tempMap = this->g->getAdjListWeights(maxEdge.second);

        for (auto it : tempMap)
        {
            get<1>(this->sigmas[it.first]) += it.second;
        }

        for (int i = 1; ((i <= nodeCount) && (i != maxEdge.first) && (i != maxEdge.second)); i++)
        {
            tempMap = this->g->getAdjListWeights(i);
            if (get<1>(this->sigmas[i]) > get<2>(this->sigmas[i]))
            {
                this->member_S.emplace(i);
                get<0>(this->sigmas[i]) = 1;

                for (auto it : tempMap)
                {
                    get<2>(this->sigmas[it.first]) += it.second;
                    if (get<0>(this->sigmas[it.first]) == 2)
                    {
                        tempW += it.second;
                    }
                }
            }
            else
            {
                this->member_S_bar.emplace(i);
                get<0>(this->sigmas[i]) = 2;

                for (auto it : tempMap)
                {
                    get<1>(this->sigmas[it.first]) += it.second;
                    if (get<0>(this->sigmas[it.first]) == 1)
                    {
                        tempW += it.second;
                    }
                }
            }
        }
        return tempW;
    }

    ll RANDOMIZED_MAXCUT()
    {
        this->member_S.clear();
        this->member_S_bar.clear();
        int nodeCount = this->g->getNodeCount();
        map<int, ll> tempMap;
        ll tempW = 0;
        for (int i = 1; i <= nodeCount; i++)
        {
            get<0>(this->sigmas[i]) = 0;
            get<1>(this->sigmas[i]) = 0;
            get<2>(this->sigmas[i]) = 0;
        }

        for (int i = 1; i <= nodeCount; i++)
        {
            tempMap = this->g->getAdjListWeights(i);
            if (coin(gen) == 0)
            {
                this->member_S.emplace(i);
                get<0>(this->sigmas[i]) = 1;
                tempMap = this->g->getAdjListWeights(i);

                for (auto it : tempMap)
                {
                    get<2>(this->sigmas[it.first]) += it.second;
                    if (get<0>(this->sigmas[it.first]) == 2)
                    {
                        tempW += it.second;
                    }
                }
            }
            else
            {
                this->member_S_bar.emplace(i);
                get<0>(this->sigmas[i]) = 2;
                tempMap = this->g->getAdjListWeights(i);

                for (auto it : tempMap)
                {
                    get<1>(this->sigmas[it.first]) += it.second;
                    if (get<0>(this->sigmas[it.first]) == 1)
                    {
                        tempW += it.second;
                    }
                }
            }
        }

        return tempW;
    }

    ll SEMI_GREEDY_MAXCUT(double alpha)
    {
        int nodeCount = this->g->getNodeCount();
        ll tempW = 0;
        map<int, ll> tempMap;
        this->member_S.clear();
        this->member_S_bar.clear();
        set<int> remainingNodes;
        for (int i = 1; i <= nodeCount; i++)
        {
            get<0>(this->sigmas[i]) = 0;
            get<1>(this->sigmas[i]) = 0;
            get<2>(this->sigmas[i]) = 0;
            remainingNodes.emplace(i);
        }

        ll wMin = this->g->getMinWeightedEdege(), wMax = this->g->getMaxWeightedEdege();
        double miu = wMin + (alpha * (wMax - wMin));
        vector<pair<int, int>> edges = this->g->getEdges();
        vector<pair<int, int>> edgesRCL;
        for (pair<int, int> p : edges)
        {
            if (g->getWeight(p.first, p.second) >= miu)
            {
                edgesRCL.emplace_back(p);
            }
        }

        uniform_int_distribution<> randomPickDist(0, edgesRCL.size() - 1);
        pair<int, int> randomEdge = edgesRCL[randomPickDist(gen)];

        this->member_S.emplace(randomEdge.first);
        get<0>(this->sigmas[randomEdge.first]) = 1;
        remainingNodes.erase(randomEdge.first);
        this->member_S_bar.emplace(randomEdge.second);
        get<0>(this->sigmas[randomEdge.second]) = 2;
        remainingNodes.erase(randomEdge.second);
        tempW += this->g->getWeight(randomEdge.first, randomEdge.second);

        int remainingNodesCount = nodeCount - 2;
        wMin = LLONG_MAX;
        wMax = LLONG_MIN;

        tempMap = this->g->getAdjListWeights(randomEdge.first);

        for (auto it : tempMap)
        {
            get<2>(this->sigmas[it.first]) += it.second;
            if (get<0>(this->sigmas[it.first]) == 0)
            {
                wMin = min(wMin, min(get<1>(this->sigmas[it.first]), get<2>(this->sigmas[it.first])));
                wMax = max(wMax, max(get<1>(this->sigmas[it.first]), get<2>(this->sigmas[it.first])));
            }
        }

        tempMap = this->g->getAdjListWeights(randomEdge.second);

        for (auto it : tempMap)
        {
            get<1>(this->sigmas[it.first]) += it.second;
            if (get<0>(this->sigmas[it.first]) == 0)
            {
                wMin = min(wMin, min(get<1>(this->sigmas[it.first]), get<2>(this->sigmas[it.first])));
                wMax = max(wMax, max(get<1>(this->sigmas[it.first]), get<2>(this->sigmas[it.first])));
            }
        }

        vector<int> nodesRCL;

        while (remainingNodesCount--)
        {
            miu = wMin + (alpha * (wMax - wMin));
            nodesRCL.clear();
            wMin = LLONG_MAX;
            wMax = LLONG_MIN;

            for (int i : remainingNodes)
            {
                if (max(get<1>(this->sigmas[i]), get<2>(this->sigmas[i])) >= miu)
                {
                    nodesRCL.emplace_back(i);
                }
            }

            // assert(nodesRCL.size() != 0);
            uniform_int_distribution<> randomIntPickDist(0, nodesRCL.size() - 1);

            int randomNode = nodesRCL[randomIntPickDist(gen)];
            remainingNodes.erase(randomNode);
            if (get<1>(this->sigmas[randomNode]) > get<2>(this->sigmas[randomNode]))
            {
                this->member_S.emplace(randomNode);
                get<0>(this->sigmas[randomNode]) = 1;
                tempMap = this->g->getAdjListWeights(randomNode);

                for (auto it : tempMap)
                {
                    get<2>(this->sigmas[it.first]) += it.second;
                    if (get<0>(this->sigmas[it.first]) == 2)
                    {
                        tempW += it.second;
                    }
                }
            }
            else
            {
                this->member_S_bar.emplace(randomNode);
                get<0>(this->sigmas[randomNode]) = 2;
                tempMap = this->g->getAdjListWeights(randomNode);

                for (auto it : tempMap)
                {
                    get<1>(this->sigmas[it.first]) += it.second;
                    if (get<0>(this->sigmas[it.first]) == 1)
                    {
                        tempW += it.second;
                    }
                }
            }

            if (remainingNodesCount == 0)
            {
                break;
            }

            for (int i : remainingNodes)
            {
                wMin = min(wMin, min(get<1>(this->sigmas[i]), get<2>(this->sigmas[i])));
                wMax = max(wMax, max(get<1>(this->sigmas[i]), get<2>(this->sigmas[i])));
            }
        }

        return tempW;
    }

    pwpss LOCAL_SEARCH_MAXCUT(pss &pS, ll tempW)
    {
        int nodeCount = this->g->getNodeCount();
        pss temp = pS;
        bool change = true;
        map<int, ll> tempMap;

        while (change)
        {
            this->LOCAL_ITER_CNT++;
            change = false;

            for (int i = 1; i <= nodeCount; i++)
            {
                if (get<0>(this->sigmas[i]) == 1)
                {
                    if (get<2>(this->sigmas[i]) > get<1>(this->sigmas[i]))
                    {
                        tempW += (get<2>(this->sigmas[i]) - get<1>(this->sigmas[i]));
                        temp.second.emplace(i);
                        temp.first.erase(i);
                        get<0>(this->sigmas[i]) = 2;
                        change = true;
                        tempMap = this->g->getAdjListWeights(i);
                        for (auto it : tempMap)
                        {
                            get<2>(this->sigmas[it.first]) -= it.second;
                            get<1>(this->sigmas[it.first]) += it.second;
                        }

                        break;
                    }
                }
                else if (get<0>(this->sigmas[i]) == 2)
                {
                    if (get<1>(this->sigmas[i]) > get<2>(this->sigmas[i]))
                    {
                        tempW += (get<1>(this->sigmas[i]) - get<2>(this->sigmas[i]));
                        temp.first.emplace(i);
                        temp.second.erase(i);
                        get<0>(this->sigmas[i]) = 1;
                        change = true;
                        tempMap = this->g->getAdjListWeights(i);
                        for (auto it : tempMap)
                        {
                            get<1>(this->sigmas[it.first]) -= it.second;
                            get<2>(this->sigmas[it.first]) += it.second;
                        }

                        break;
                    }
                }
            }
        }

        return make_pair(tempW, temp);
    }

    void GRASP_MAXCUT(int fileID, int GRASP_ITERATION, double alpha)
    {
        ll wStar, tempW;
        wStar = this->LOCAL_CUM_W = this->GREEDY_LOCAL_W;
        this->RAND_CUM_W = this->SEMI_GREEDY_CUM_W = 0;
        this->LOCAL_ITER_CNT = 1;
        pss tempStar;
        pwpss tempLocal;
        for (int i = 0; i < GRASP_ITERATION; i++)
        {
            tempW = this->RANDOMIZED_MAXCUT();
            this->RAND_CUM_W += tempW;
            tempLocal.second = make_pair(this->member_S, this->member_S_bar);
            tempLocal = this->LOCAL_SEARCH_MAXCUT(tempLocal.second, tempW);
            tempW = tempLocal.first;
            this->LOCAL_CUM_W += tempW;

            if (tempW > wStar)
            {
                wStar = tempW;
                tempStar = tempLocal.second;
            }

            tempW = this->SEMI_GREEDY_MAXCUT(alpha);
            this->SEMI_GREEDY_CUM_W += tempW;
            tempLocal.second = make_pair(this->member_S, this->member_S_bar);
            tempLocal = this->LOCAL_SEARCH_MAXCUT(tempLocal.second, tempW);
            tempW = tempLocal.first;
            this->LOCAL_CUM_W += tempW;

            if (tempW > wStar)
            {
                wStar = tempW;
                tempStar = tempLocal.second;
            }
        }
        cout << 'G' << fileID << ','
             << this->g->getNodeCount() << ','
             << this->g->getEdgeCount() << ','
             << alpha << ','
             << this->GREEDY_W << ','
             << (this->RAND_CUM_W / GRASP_ITERATION) << ','
             << (this->SEMI_GREEDY_CUM_W / GRASP_ITERATION) << ','
             << (this->LOCAL_ITER_CNT / (GRASP_ITERATION * 2 + 1)) << ','
             << (this->LOCAL_CUM_W / (GRASP_ITERATION * 2 + 1)) << ','
             << GRASP_ITERATION << ','
             << wStar << ','
             << bestKnownBound[fileID] << '\n';
    }
};

int main(int argc, char *argv[])
{

    bestKnownBound[1] = "12078";
    bestKnownBound[2] = "12084";
    bestKnownBound[3] = "12077";
    bestKnownBound[11] = "627";
    bestKnownBound[12] = "621";
    bestKnownBound[13] = "645";

    bestKnownBound[14] = "3187";
    bestKnownBound[15] = "3169";
    bestKnownBound[16] = "3172";
    bestKnownBound[22] = "14123";
    bestKnownBound[23] = "14129";
    bestKnownBound[24] = "14131";

    bestKnownBound[32] = "1560";
    bestKnownBound[33] = "1537";
    bestKnownBound[34] = "1541";
    bestKnownBound[35] = "8000";
    bestKnownBound[36] = "7996";
    bestKnownBound[37] = "8009";

    bestKnownBound[43] = "7027";
    bestKnownBound[44] = "7022";
    bestKnownBound[45] = "7020";
    bestKnownBound[48] = "6000";
    bestKnownBound[49] = "6000";
    bestKnownBound[50] = "5988";

    int n, m, u, v;
    ll w;
    cin >> n >> m;

    Graph g(n, m);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    MaxCut boss(&g);

    int GRASP_ITERATIONS[] = {20, 50, 100, 500, 1000};

    for (double alpha = 0.0; alpha <= 1.00; alpha += 0.1)
    {
        for (int i = 0; i < ((sizeof(GRASP_ITERATIONS)) / (sizeof(GRASP_ITERATIONS[0]))); i++)
        {
            boss.GRASP_MAXCUT(atoi(argv[1]), GRASP_ITERATIONS[i], alpha);
        }
    }

    return 0;
}
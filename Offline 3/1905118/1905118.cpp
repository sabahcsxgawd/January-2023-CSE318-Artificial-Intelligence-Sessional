#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pss pair<set<int>, set<int>>
#define pwpss pair<ll, pss>
#define ELITE_POOL_SIZE 10
#define GRASP_ITERATIONS 20

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dist(0.0, 1.0);

class Graph
{

private:
    int nodeCount, edgeCount;
    ll minWeightedEdge, maxWeightedEdge;
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

    pwpss N(pss &pS, pss &pG)
    {
        pss temp = pS, best;
        ll w = LLONG_MIN, tempW;

        for (auto it = pG.first.begin(); it != pG.first.end(); it++)
        {
            if ((pG.first.find(*it) != pG.first.end()) && !(pS.first.find(*it) != pS.first.end()))
            {
                temp.first.emplace(*it);
                temp.second.erase(*it);
                tempW = g->getMaxCutWeight(temp.first, temp.second);
                if (tempW > w)
                {
                    best = temp;
                    w = tempW;
                }
                temp.first.erase(*it);
                temp.second.emplace(*it);
            }
        }

        for (auto it = pS.first.begin(); it != pS.first.end(); it++)
        {
            if ((pS.first.find(*it) != pS.first.end()) && !(pG.first.find(*it) != pG.first.end()))
            {
                temp.first.erase(*it);
                temp.second.emplace(*it);
                tempW = g->getMaxCutWeight(temp.first, temp.second);
                if (tempW > w)
                {
                    best = temp;
                    w = tempW;
                }
                temp.second.erase(*it);
                temp.first.emplace(*it);
            }
        }

        return make_pair(w, best);
    }

    pss LOCAL_SEARCH_MAXCUT(pss &pS)
    {
        bool change = true;
        int nodeCount = g->getNodeCount();
        pss temp = pS;

        while (change)
        {
            change = false;
            for (int i = 1; (i <= nodeCount) && !change; i++)
            {
                if (temp.first.find(i) != temp.first.end())
                {
                    if (this->g->getSigmaY(i, temp.first) > this->g->getSigmaX(i, temp.second))
                    {
                        change = true;
                        temp.second.emplace(i);
                        temp.first.erase(i);
                    }
                }
                else
                {
                    if (this->g->getSigmaX(i, temp.second) > this->g->getSigmaY(i, temp.first))
                    {
                        change = true;
                        temp.first.emplace(i);
                        temp.second.erase(i);
                    }
                }
            }
        }

        return temp;
    }

    pwpss new_LOCAL_SEARCH_MAXCUT(pss &pS)
    {
        int nodeCount = this->g->getNodeCount();
        pss temp = pS;
        ll tempW = 0;
        bool change = true;
        int localIterationCnt = 0;
        map<int, ll> tempMap;

        while (change)
        {
            localIterationCnt++;
            change = false;

            for (int i = 1; i <= nodeCount; i++)
            {
                if (get<0>(this->sigmas[i]) == 1)
                {
                    if (get<2>(this->sigmas[i]) > get<1>(this->sigmas[i]))
                    {
                        temp.second.emplace(i);
                        temp.first.erase(i);
                        get<0>(this->sigmas[i]) = 2;
                        change = true;
                        // for (int j = 1; j <= nodeCount; j++)
                        // {
                        //     get<2>(this->sigmas[j]) -= this->g->getWeight(j, i);
                        //     get<1>(this->sigmas[j]) += this->g->getWeight(j, i);
                        // }
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
                        temp.first.emplace(i);
                        temp.second.erase(i);
                        get<0>(this->sigmas[i]) = 1;
                        change = true;
                        // for (int j = 1; j <= nodeCount; j++)
                        // {
                        //     get<1>(this->sigmas[j]) -= this->g->getWeight(j, i);
                        //     get<2>(this->sigmas[j]) += this->g->getWeight(j, i);
                        // }
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

        if (temp.first.size() > temp.second.size())
        {
            for (int i : temp.second)
            {
                tempW += get<2>(this->sigmas[i]);
            }
        }
        else
        {
            for (int i : temp.first)
            {
                tempW += get<1>(this->sigmas[i]);
            }
        }
        // for (int i = 1; i <= nodeCount; i++)
        // {
        //     if (get<0>(this->sigmas[i]) == 1)
        //     {
        //         tempW += get<1>(this->sigmas[i]);
        //     }
        // }
        // cout << localIterationCnt << ' ';
        assert(tempW == this->g->getMaxCutWeight(temp.first, temp.second));
        return make_pair(tempW, temp);
    }

public:
    MaxCut() = delete;

    MaxCut(const MaxCut &) = delete;

    MaxCut(Graph *g)
    {
        this->g = g;
        this->sigmas.resize(g->getNodeCount() + 1, make_tuple(0, 0, 0));
    }

    ll SEMI_GREEDY_MAXCUT()
    {
        double alpha = dist(gen);
        ll wMin = this->g->getMinWeightedEdege(), wMax = this->g->getMaxWeightedEdege();
        double miu = wMin + (alpha * (wMax - wMin));
        vector<pair<int, int>> edges = this->g->getEdges(); // TODO custom sort
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
        this->member_S.clear();
        this->member_S_bar.clear();
        this->member_S.emplace(randomEdge.first);
        this->member_S_bar.emplace(randomEdge.second);
        int nodeCount = this->g->getNodeCount();
        set<int> nodeTracker;
        for (int i = 1; i <= nodeCount; i++)
        {
            nodeTracker.emplace(i);
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
                minSigmaX = min(minSigmaX, this->g->getSigmaX(*it, this->member_S_bar));
                minSigmaY = min(minSigmaY, this->g->getSigmaY(*it, this->member_S));
                maxSigmaX = max(maxSigmaX, this->g->getSigmaX(*it, this->member_S_bar));
                maxSigmaY = max(maxSigmaY, this->g->getSigmaY(*it, this->member_S));
            }

            wMin = min(minSigmaX, minSigmaY);
            wMax = max(maxSigmaX, maxSigmaY);

            miu = wMin + (alpha * (wMax - wMin));
            nodesRCL.clear();

            for (auto it = nodeTracker.begin(); it != nodeTracker.end(); it++)
            {
                if (max(this->g->getSigmaX(*it, this->member_S_bar), this->g->getSigmaY(*it, this->member_S)) >= miu)
                {
                    nodesRCL.emplace_back(*it);
                }
            }

            uniform_int_distribution<> randomIntPickDist(0, nodesRCL.size() - 1);

            int randomNode = nodesRCL[randomIntPickDist(gen)];

            if (this->g->getSigmaX(randomNode, this->member_S_bar) > this->g->getSigmaY(randomNode, this->member_S))
            {
                nodeTracker.erase(randomNode);
                this->member_S.emplace(randomNode);
            }
            else
            {
                nodeTracker.erase(randomNode);
                this->member_S_bar.emplace(randomNode);
            }
        }

        return this->g->getMaxCutWeight(this->member_S, this->member_S_bar);
    }

    void new_SEMI_GREEDY_MAXCUT(double alpha)
    {
        int nodeCount = this->g->getNodeCount();
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

        int remainingNodesCount = nodeCount - 2;
        wMin = LLONG_MAX;
        wMax = LLONG_MIN;

        // for (int i = 1; i <= nodeCount; i++)
        // {
        //     get<1>(this->sigmas[i]) = this->g->getSigmaX(i, this->member_S_bar);
        //     get<2>(this->sigmas[i]) = this->g->getSigmaY(i, this->member_S);
        //     if (get<0>(this->sigmas[i]) == 0)
        //     {
        //         wMin = min(wMin, min(get<1>(this->sigmas[i]), get<2>(this->sigmas[i])));
        //         wMax = max(wMax, max(get<1>(this->sigmas[i]), get<2>(this->sigmas[i])));
        //     }
        // }

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

            // for (int i = 1; i <= nodeCount; i++)
            // {
            //     if ((get<0>(this->sigmas[i]) == 0) && (max(get<1>(this->sigmas[i]), get<2>(this->sigmas[i])) >= miu))
            //     {
            //         nodesRCL.emplace_back(i);
            //     }
            // }

            for (int i : remainingNodes)
            {
                if (max(get<1>(this->sigmas[i]), get<2>(this->sigmas[i])) >= miu)
                {
                    nodesRCL.emplace_back(i);
                }
            }

            assert(nodesRCL.size() != 0);
            uniform_int_distribution<> randomIntPickDist(0, nodesRCL.size() - 1);

            int randomNode = nodesRCL[randomIntPickDist(gen)];
            remainingNodes.erase(randomNode);
            if (get<1>(this->sigmas[randomNode]) > get<2>(this->sigmas[randomNode]))
            {
                this->member_S.emplace(randomNode);
                get<0>(this->sigmas[randomNode]) = 1;
                // for (int i = 1; i <= nodeCount; i++)
                // {
                //     get<2>(this->sigmas[i]) += this->g->getWeight(i, randomNode);
                // }
                tempMap = this->g->getAdjListWeights(randomNode);

                for (auto it : tempMap)
                {
                    get<2>(this->sigmas[it.first]) += it.second;
                }
            }
            else
            {
                this->member_S_bar.emplace(randomNode);
                get<0>(this->sigmas[randomNode]) = 2;
                // for (int i = 1; i <= nodeCount; i++)
                // {
                //     get<1>(this->sigmas[i]) += this->g->getWeight(i, randomNode);
                // }
                tempMap = this->g->getAdjListWeights(randomNode);

                for (auto it : tempMap)
                {
                    get<1>(this->sigmas[it.first]) += it.second;
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

        // return this->g->getMaxCutWeight(this->member_S, this->member_S_bar);
    }

    pwpss PATH_RELINKING_MAXCUT(pss &pS, pss &pG)
    {
        pss tempPSS1, tempPSS2, tempStar;
        ll wStar = LLONG_MIN;

        pwpss tempN = this->N(pS, pG);
        pss prevN1, prevN2;

        int limit = 100;

        while (tempN.first != LLONG_MIN && limit--)
        {
            if (tempN.first > wStar)
            {
                wStar = tempN.first;
                tempStar = tempN.second;
            }
            prevN1 = tempN.second;
            tempN = this->N(tempN.second, pG);
            if (prevN1 == tempN.second)
                break;
        }

        tempPSS1 = this->LOCAL_SEARCH_MAXCUT(tempStar);

        wStar = LLONG_MIN;
        limit = 100;
        swap(pG.first, pG.second);
        tempN = this->N(pS, pG);
        while (tempN.first != LLONG_MIN && limit--)
        {
            if (tempN.first > wStar)
            {
                wStar = tempN.first;
                tempStar = tempN.second;
            }
            prevN2 = tempN.second;
            tempN = this->N(tempN.second, pG);
            if (prevN2 == tempN.second)
                break;
        }

        tempPSS2 = this->LOCAL_SEARCH_MAXCUT(tempStar);
        swap(pG.first, pG.second);
        ll w1 = g->getMaxCutWeight(tempPSS1.first, tempPSS1.second);
        ll w2 = g->getMaxCutWeight(tempPSS2.first, tempPSS2.second);

        if (w1 > w2)
        {
            return make_pair(w1, tempPSS1);
        }
        else
        {
            return make_pair(w2, tempPSS2);
        }
    }

    ll GRASP_PR_MAXCUT()
    {
        int cnt = 0;
        ll wStar = LLONG_MIN, tempW;
        set<pwpss> ELITE_POOL;
        pwpss randomElite;
        pss pG, tempLocal, tempStar;

        for (int i = 0; i < GRASP_ITERATIONS; i++)
        {
            this->SEMI_GREEDY_MAXCUT();
            tempLocal = make_pair(this->member_S, this->member_S_bar);
            tempLocal = this->LOCAL_SEARCH_MAXCUT(tempLocal);
            tempW = g->getMaxCutWeight(tempLocal.first, tempLocal.second);

            if (cnt == 0)
            {
                cnt++;
                ELITE_POOL.emplace(make_pair(tempW, tempLocal));
            }

            else
            {
                uniform_int_distribution<> randomElitePick(0, cnt - 1);
                auto it = ELITE_POOL.begin();
                advance(it, randomElitePick(gen));
                pG = (*it).second;
                randomElite = this->PATH_RELINKING_MAXCUT(tempLocal, pG);
                tempLocal = randomElite.second;
                tempW = randomElite.first;
                ELITE_POOL.emplace(randomElite);

                if (cnt < ELITE_POOL_SIZE)
                {
                    cnt = ELITE_POOL.size();
                }
                else
                {

                    ELITE_POOL.erase(ELITE_POOL.begin());
                }
            }

            if (tempW > wStar)
            {
                wStar = tempW;
                tempStar = tempLocal;
            }
        }

        this->member_S = tempStar.first;
        this->member_S_bar = tempStar.second;

        return wStar;
    }

    ll GRASP_MAXCUT(double alpha)
    {
        ll wStar = LLONG_MIN, tempW;
        pss tempStar;
        pwpss tempLocal;

        // double alpha = dist(gen);

        for (int i = 0; i < 10; i++)
        {
            this->new_SEMI_GREEDY_MAXCUT(alpha);
            tempLocal.second = make_pair(this->member_S, this->member_S_bar);
            tempLocal = this->new_LOCAL_SEARCH_MAXCUT(tempLocal.second);
            tempW = tempLocal.first;
            // assert(tempW == this->g->getMaxCutWeight(tempLocal.second.first, tempLocal.second.second));

            if (tempW > wStar)
            {
                wStar = tempW;
                tempStar = tempLocal.second;
            }
        }
        cout << alpha << ' ';
        return wStar;
    }

    void dummyTest()
    {
        this->SEMI_GREEDY_MAXCUT();
        pss pS = make_pair(this->member_S, this->member_S_bar);
        cout << g->getMaxCutWeight(pS.first, pS.second) << '\n';

        pss pG = this->LOCAL_SEARCH_MAXCUT(pS);
        cout << g->getMaxCutWeight(pG.first, pG.second) << '\n';

        this->SEMI_GREEDY_MAXCUT();
        pS = make_pair(this->member_S, this->member_S_bar);
        cout << g->getMaxCutWeight(pS.first, pS.second) << '\n';

        pS = this->LOCAL_SEARCH_MAXCUT(pS);
        cout << g->getMaxCutWeight(pS.first, pS.second) << '\n';

        pwpss gg = this->PATH_RELINKING_MAXCUT(pS, pG);
        cout << g->getMaxCutWeight(gg.second.first, gg.second.second) << '\n';
    }
};

int main(int argc, char *argv[])
{

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

    // cout << boss.GRASP_PR_MAXCUT() << '\n';
    // for(double alpha = 0.1; alpha <= 1.00; alpha += 0.1) {
    cout << boss.GRASP_MAXCUT(dist(gen)) << '\n';
    // }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pss pair<set<int>, set<int>>
#define pwpss pair<ll, pss>
#define ELITE_POOL_SIZE 3

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
        this->edges.reserve(edgeCount);
    }

    void addEdge(int u, int v, ll w)
    {
        this->weights[u][v] = w;
        this->weights[v][u] = w;
        this->minWeightedEdge = min(this->minWeightedEdge, w);
        this->maxWeightedEdge = max(this->maxWeightedEdge, w);
        this->edges.emplace_back(make_pair(u, v));
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
    set<int> member_S, member_S_bar;

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

        return make_pair(w, temp);
    }

    pss LOCAL_SEARCH_MAXCUT(pss& pS)
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

            assert(nodesRCL.size() > 0);

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

    pwpss PATH_RELINKING_MAXCUT(pss &pS, pss &pG)
    {
        pss tempPSS1, tempPSS2, tempStar;        
        ll wStar = LLONG_MIN;

        pwpss tempN = this->N(pS, pG);
        pss prevN1, prevN2;    

        while (tempN.first != LLONG_MIN)
        {
            
            if(tempStar == tempN.second) break;

            if(tempN.first > wStar) {
                wStar = tempN.first;
                tempStar = tempN.second;
            }
            prevN1 = tempN.second;
            tempN = this->N(tempN.second, pG);
            if(prevN1 == tempN.second) break;
        }

        tempPSS1 = this->LOCAL_SEARCH_MAXCUT(tempStar);

        wStar = LLONG_MIN;
        swap(pG.first, pG.second);
        tempN = this->N(pS, pG);
        while (tempN.first != LLONG_MIN)
        {
            if(tempStar == tempN.second) break;

            if(tempN.first > wStar) {
                wStar = tempN.first;
                tempStar = tempN.second;
            }            
            prevN2 = tempN.second;
            tempN = this->N(tempN.second, pG);
            if(prevN2 == tempN.second) break;
        }

        tempPSS2 = this->LOCAL_SEARCH_MAXCUT(tempStar);
        swap(pG.first, pG.second);
        ll w1 = g->getMaxCutWeight(tempPSS1.first, tempPSS1.second);
        ll w2 = g->getMaxCutWeight(tempPSS2.first, tempPSS2.second);

        if(w1 > w2) {
            return make_pair(w1, tempPSS1);
        }
        else {
            return make_pair(w2, tempPSS2);
        }
    }

    // ll GRASP_PR_MAXCUT()
    // {
    //     ll w_Star = LLONG_MIN;
    //     ll *tempW;
    //     pss S_star, tempLocal;
    //     pair<pss, ll> elitePool[ELITE_POOL_SIZE];
    //     ll bestW_pool = LLONG_MIN, worstW_pool = LLONG_MAX;
    //     int bestIndex_pool = -1, worstIndex_pool = -1, count = 0;
    //     for (int i = 0; i < 6; i++)
    //     {
    //         this->member_MAXCUT();
    //         tempLocal = this->LOCAL_SEARCH_MAXCUT(this->member_S, this->member_S_bar);

    //         if (count > 0)
    //         {
    //             uniform_int_distribution<> randomPoolPick(0, count - 1);
    //             pss pG = elitePool[randomPoolPick(gen)].first;
    //             tempLocal = this->PATH_RELINKING_MAXCUT(tempLocal, pG, tempW);
    //         }

    //         if (count < ELITE_POOL_SIZE)
    //         {
    //             elitePool[count++] = make_pair(tempLocal, *tempW);
    //             if (*tempW > bestW_pool)
    //             {
    //                 bestW_pool = *tempW;
    //                 bestIndex_pool = count - 1;
    //             }
    //             if (*tempW < worstW_pool)
    //             {
    //                 worstIndex_pool = *tempW;
    //                 worstIndex_pool = count - 1;
    //             }
    //         }

    //         if (count == ELITE_POOL_SIZE)
    //         {
    //             if (*tempW > worstW_pool)
    //             {
    //                 elitePool[worstIndex_pool] = make_pair(tempLocal, *tempW);
    //                 bestW_pool = worstW_pool = elitePool[0].second;
    //                 bestIndex_pool = worstIndex_pool = 0;
    //                 for (int j = 1; j < ELITE_POOL_SIZE; j++)
    //                 {
    //                     if (elitePool[j].second > bestW_pool)
    //                     {
    //                         bestIndex_pool = j;
    //                         bestW_pool = elitePool[j].second;
    //                     }
    //                     if (elitePool[j].second < worstW_pool)
    //                     {
    //                         worstIndex_pool = j;
    //                         worstW_pool = elitePool[j].second;
    //                     }
    //                 }
    //             }
    //         }

    //         if (bestW_pool > w_Star)
    //         {
    //             w_Star = bestW_pool;
    //             S_star = elitePool[bestIndex_pool].first;
    //         }
    //     }

    //     return w_Star;
    // }

    void dummyTest()
    {
        this->SEMI_GREEDY_MAXCUT();
        pss pS = make_pair(this->member_S, this->member_S_bar);
        cout << g->getMaxCutWeight(pS.first, pS.second) << '\n';
        
        pss pG = this->LOCAL_SEARCH_MAXCUT(pS);
        cout << g->getMaxCutWeight(pG.first, pG.second) << '\n';

        pwpss gg = this->PATH_RELINKING_MAXCUT(pS, pG);
        cout << g->getMaxCutWeight(gg.second.first, gg.second.second) << '\n';
        
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

    MaxCut boss(g);

    boss.dummyTest();

    delete g;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pss pair<set<int>, set<int>>
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
    set<int> SEMI_GREEDY_S, SEMI_GREEDY_S_bar;

    set<pss> N(pss &pS, pss &pG)
    {
        set<pss> pN, mN;
        pN = N_plus(pS, pG);
        mN = N_minus(pS, pG);
        if (pN.size() < mN.size())
        {
            swap(pN, mN);
        }
        for (auto it = mN.begin(); it != mN.end(); it++)
        {
            pN.emplace(*it);
        }
        return pN;
    }

    set<pss> N_plus(pss &pS, pss &pG)
    {
        set<pss> N_plus;
        for (auto it = pG.first.begin(); it != pG.first.end(); it++)
        {
            if ((pG.first.find(*it) != pG.first.end()) && !(pS.first.find(*it) != pS.first.end()))
            {
                pS.first.emplace(*it);
                pS.second.erase(*it);
                N_plus.insert(make_pair(pS.first, pS.second));
                pS.first.erase(*it);
                pS.second.emplace(*it);
            }
        }
        return N_plus;
    }

    set<pss> N_minus(pss &pS, pss &pG)
    {
        set<pss> N_minus;
        for (auto it = pS.first.begin(); it != pS.first.end(); it++)
        {
            if ((pS.first.find(*it) != pS.first.end()) && !(pG.first.find(*it) != pG.first.end()))
            {
                pS.first.erase(*it);
                pS.second.emplace(*it);
                N_minus.insert(make_pair(pS.first, pS.second));
                pS.first.emplace(*it);
                pS.second.erase(*it);
            }
        }
        return N_minus;
    }

    pss LOCAL_SEARCH_MAXCUT(set<int> &S, set<int> &S_bar)
    {    
        bool change = true;

        while (change)
        {
            change = false;
            for (int i = 1; (i <= g->getNodeCount()) && !change; i++)
            {
                if (S.find(i) != S.end())
                {
                    if (this->g->getSigmaY(i, S) > this->g->getSigmaX(i, S_bar))
                    {
                        change = true;
                        S_bar.emplace(i);
                        S.erase(i);
                    }
                }
                else
                {
                    if (this->g->getSigmaX(i, S_bar) > this->g->getSigmaY(i, S))
                    {
                        change = true;
                        S.emplace(i);
                        S_bar.erase(i);
                    }
                }
            }
        }

        return make_pair(S, S_bar);
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
                edgesRCL.push_back(p);
            }
        }
        uniform_int_distribution<> randomPickDist(0, edgesRCL.size() - 1);
        pair<int, int> randomEdge = edgesRCL[randomPickDist(gen)];
        this->SEMI_GREEDY_S.clear();
        this->SEMI_GREEDY_S_bar.clear();
        this->SEMI_GREEDY_S.emplace(randomEdge.first);
        this->SEMI_GREEDY_S_bar.emplace(randomEdge.second);
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
                this->SEMI_GREEDY_S.emplace(randomNode);
            }
            else
            {
                nodeTracker.erase(randomNode);
                this->SEMI_GREEDY_S_bar.emplace(randomNode);
            }
        }

        return this->g->getMaxCutWeight(this->SEMI_GREEDY_S, this->SEMI_GREEDY_S_bar);
    }

    pss PATH_RELINKING_MAXCUT(pss &pS, pss &pG, ll *weightPass)
    {
        set<int> S = pS.first;
        set<int> S_bar = pS.second;
        set<int> S_plus, S_plus_bar, S_star, S_star_bar;
        // pss pS = make_pair(S, S_bar);
        pss tempPSS1, tempPSS2;
        set<pss> NS = this->N(pS, pG);
        ll wStar = LLONG_MIN, w1 = LLONG_MIN;

        while (NS.size() > 0)
        {
            ll tempW;
            for (auto it = NS.begin(); it != NS.end(); it++)
            {
                tempW = g->getMaxCutWeight((*it).first, (*it).second);
                if (tempW > w1)
                {
                    S_plus = (*it).first;
                    S_plus_bar = (*it).second;
                    w1 = tempW;
                }
            }
            S = S_plus;
            S_bar = S_plus_bar;
            if (w1 > wStar)
            {
                S_star = S;
                S_star_bar = S_bar;
                wStar = w1;
            }
        }

        tempPSS1 = this->LOCAL_SEARCH_MAXCUT(S_star, S_star_bar);

        S = pS.first;
        S_bar = pS.second;
        wStar = LLONG_MIN, w1 = LLONG_MIN;
        swap(pG.first, pG.second);
        NS = this->N(pS, pG);

        while (NS.size() > 0)
        {
            ll tempW;
            for (auto it = NS.begin(); it != NS.end(); it++)
            {
                tempW = g->getMaxCutWeight((*it).first, (*it).second);
                if (tempW > w1)
                {
                    S_plus = (*it).first;
                    S_plus_bar = (*it).second;
                    w1 = tempW;
                }
            }
            S = S_plus;
            S_bar = S_plus_bar;
            if (w1 > wStar)
            {
                S_star = S;
                S_star_bar = S_bar;
                wStar = w1;
            }
        }

        tempPSS2 = this->LOCAL_SEARCH_MAXCUT(S_star, S_star_bar);

        ll weight1 = g->getMaxCutWeight(tempPSS1.first, tempPSS1.second);
        ll weight2 = g->getMaxCutWeight(tempPSS2.first, tempPSS2.second);

        if(weight1 > weight2) {
            *weightPass = weight1;
            return tempPSS1;
        }
        else {
            *weightPass = weight2;
            return tempPSS2;
        }
    }

    ll GRASP_PR_MAXCUT() {
        ll w_Star = LLONG_MIN;
        ll *tempW;
        pss S_star, tempLocal;
        pair<pss, ll> elitePool[ELITE_POOL_SIZE];
        ll bestW_pool = LLONG_MIN, worstW_pool = LLONG_MAX;
        int bestIndex_pool = -1, worstIndex_pool = -1, count = 0;
        for(int i = 0; i < 6; i++) {
            this->SEMI_GREEDY_MAXCUT();
            tempLocal = this->LOCAL_SEARCH_MAXCUT(this->SEMI_GREEDY_S, this->SEMI_GREEDY_S_bar);
            
            if(count > 0) {
                uniform_int_distribution<>randomPoolPick(0, count - 1);
                pss pG = elitePool[randomPoolPick(gen)].first;
                tempLocal = this->PATH_RELINKING_MAXCUT(tempLocal, pG, tempW);
            }

            if(count < ELITE_POOL_SIZE) {
                elitePool[count++] = make_pair(tempLocal, *tempW);
                if(*tempW > bestW_pool) {
                    bestW_pool = *tempW;
                    bestIndex_pool = count - 1;
                }
                if(*tempW < worstW_pool) {
                    worstIndex_pool = *tempW;
                    worstIndex_pool = count - 1;
                }
            }

            if(count == ELITE_POOL_SIZE) {
                if(*tempW > worstW_pool) {
                    elitePool[worstIndex_pool] = make_pair(tempLocal, *tempW);
                    bestW_pool = worstW_pool = elitePool[0].second;
                    bestIndex_pool = worstIndex_pool = 0;
                    for(int j = 1; j < ELITE_POOL_SIZE; j++) {
                        if(elitePool[j].second > bestW_pool) {
                            bestIndex_pool = j;
                            bestW_pool = elitePool[j].second;
                        }
                        if(elitePool[j].second < worstW_pool) {
                            worstIndex_pool = j;
                            worstW_pool = elitePool[j].second;
                        }
                    }
                }
            }

            if(bestW_pool > w_Star) {
                w_Star = bestW_pool;
                S_star = elitePool[bestIndex_pool].first;
            }
        }

        return w_Star;
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

    // MaxCut semi_greedy_solver(g);

    // cout << semi_greedy_solver.SEMI_GREEDY_MAXCUT() << '\n';

    MaxCut boss(g);

    cout << boss.GRASP_PR_MAXCUT() << '\n';

    delete g;

    return 0;
}
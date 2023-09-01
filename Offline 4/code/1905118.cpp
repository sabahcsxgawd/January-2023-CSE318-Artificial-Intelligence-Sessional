#include <bits/stdc++.h>
using namespace std;

class Node
{

private:
    int attributeIndex;
    string outcome;
    vector<Node *> children;

public:
    Node(const Node &) = delete;

    Node()
    {
        this->outcome = "";
    }

    void setAttributeIndex(int attributeIndex)
    {
        this->attributeIndex = attributeIndex;
    }

    void setOutcome(const string &outcome)
    {
        this->outcome = outcome;
    }

    void addChildren(Node *node)
    {
        this->children.emplace_back(node);
    }

    int getAttributeIndex()
    {
        return this->attributeIndex;
    }

    string getOutcome()
    {
        return this->outcome;
    }

    vector<Node *> getChildren()
    {
        return this->children;
    }

    ~Node()
    {
        for (Node *child : this->children)
        {
            if (child != NULL)
            {
                delete child;
            }
        }
    }
};

class DecisionTree
{

private:
    int howManyAttrs, howManyExamples, goalIndex;
    vector<vector<int>> trainingData, testData; // training is actually examples
    vector<int> howManyValsPerAttr;
    map<int, string> goalClassValues;

    Node *root;

    bool isEmpty(const string &s)
    {
        for (char c : s)
        {
            if (c == '1')
            {
                return false;
            }
        }
        return true;
    }

    double myLog(double p)
    {
        if (p > 0.0)
        {
            return log2(p);
        }
        else
        {
            return 0.0;
        }
    }

    double getEntropy(const vector<int> &v)
    {
        double total, multPart, entropy;
        total = multPart = 0.0;
        for (int x : v)
        {
            total += (double)x;
            if (total == 0)
                multPart += ((double)x * myLog(x));
        }

        if (total == 0)
        {
            return 0;
        }

        entropy = myLog(total) - (multPart / total);
        return entropy;
    }

    double getInitialEntropy(const string &exampleBitMap)
    {
        vector<int> goalClassValues(this->howManyValsPerAttr[this->goalIndex], 0);
        int i = 0;
        for (char c : exampleBitMap)
        {
            if (c == '1')
            {
                goalClassValues[this->trainingData[i][goalIndex]]++;
            }
            i++;
        }

        return this->getEntropy(goalClassValues);
    }

    double getRemainder(const int attributeIndex, const string &exampleBitMap)
    {
        vector<vector<int>> subsetData(this->howManyValsPerAttr[attributeIndex], vector<int>(this->howManyValsPerAttr[this->goalIndex], 0));
        int i = 0, cnt = 0;
        for (char c : exampleBitMap)
        {
            if (c == '1')
            {
                subsetData[this->trainingData[i][attributeIndex]][this->trainingData[i][this->goalIndex]]++;
                cnt++;
            }
            i++;
        }
        double remainder = 0.0;

        for (auto v : subsetData)
        {
            remainder += ((accumulate(v.begin(), v.end(), 0) * 1.0 / cnt) * this->getEntropy(v));
        }
        return remainder;
    }

    Node *getPluralityValue(const string &exampleBitMap)
    {
        vector<int> goalClassValues(this->howManyValsPerAttr[this->goalIndex], 0);
        int i = 0;
        for (char c : exampleBitMap)
        {
            if (c == '1')
            {
                goalClassValues[this->trainingData[i][goalIndex]]++;
            }
            i++;
        }
        int maxGoalClassIndex = 0;
        for (i = 1; i < goalClassValues.size(); i++)
        {
            if (goalClassValues[i] > goalClassValues[maxGoalClassIndex])
            {
                maxGoalClassIndex = i;
            }
        }
        Node *rv = new Node();
        rv->setAttributeIndex(goalIndex);
        rv->setOutcome(this->goalClassValues[maxGoalClassIndex]);
        return rv;
    }

    int isSameClassification(const string &exampleBitMap)
    {
        int fixedGoalClassIndex = -1;
        int i = 0;
        for (char c : exampleBitMap)
        {
            if (c == '1')
            {
                if (fixedGoalClassIndex == -1)
                {
                    fixedGoalClassIndex = this->trainingData[i][this->goalIndex];
                }
                else
                {
                    if (fixedGoalClassIndex != this->trainingData[i][this->goalIndex])
                    {
                        return -1;
                    }
                }
            }
            i++;
        }
        return fixedGoalClassIndex;
    }

public:
    DecisionTree(const DecisionTree &) = delete;

    DecisionTree()
    {
        this->howManyAttrs = this->howManyExamples = this->goalIndex = 0;
        this->root = NULL;
    }

    void feedData(const string &data)
    {
        // asssuming test data is in same folder with correct file name
        ifstream inFile(data);
        string line, token;
        vector<int> replaceAttrValues;
        vector<string> tempAttrValues;
        vector<vector<string>> tempData;
        map<pair<int, string>, int> attrValMapper;
        map<int, int> attrValMapper2;
        stringstream ss;
        while (getline(inFile, line))
        {
            tempAttrValues.clear();
            int attrIndex = 0;
            ss.str(line);
            while (getline(ss, token, ','))
            {
                tempAttrValues.emplace_back(token);
                if (attrValMapper.find({attrIndex, token}) == attrValMapper.end())
                {
                    attrValMapper[{attrIndex, token}] = attrValMapper2[attrIndex]++;
                }
                attrIndex++;
            }
            ss.clear();
            tempData.emplace_back(tempAttrValues);
        }

        this->trainingData.clear();
        this->testData.clear();

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 100);

        this->howManyAttrs = this->goalIndex = tempData[0].size() - 1;

        for (int i = 0; i < tempData.size(); i++)
        {
            for (int j = 0; j < tempData[i].size(); j++)
            {
                replaceAttrValues.emplace_back(attrValMapper[{j, tempData[i][j]}]);
                if (j == this->goalIndex && this->goalClassValues.find(replaceAttrValues.back()) == this->goalClassValues.end())
                {
                    this->goalClassValues[replaceAttrValues.back()] = tempData[i][j];
                }
            }
            if (dist(gen) > 80)
            {
                this->testData.emplace_back(replaceAttrValues);
            }
            else
            {
                this->trainingData.emplace_back(replaceAttrValues);
            }
            replaceAttrValues.clear();
        }

        // assuming all examples have all attributes
        this->howManyExamples = this->trainingData.size();
        this->howManyValsPerAttr.resize(this->howManyAttrs + 1);

        for (int i = 0; i <= this->howManyAttrs; i++)
        {
            this->howManyValsPerAttr[i] = attrValMapper2[i];
        }

        inFile.close();
    }

    Node *learnByInfoGain(string exampleBitMap, string attributeBitMap, string parentExampleBitMap)
    {
        int sameGoalClass = -1;
        if (this->isEmpty(exampleBitMap))
        {
            return this->getPluralityValue(parentExampleBitMap);
        }
        else if ((sameGoalClass = this->isSameClassification(exampleBitMap)) != -1)
        {
            Node *rv = new Node();
            rv->setAttributeIndex(this->goalIndex);
            rv->setOutcome(this->goalClassValues[sameGoalClass]);
            return rv;
        }
        else if (this->isEmpty(attributeBitMap))
        {
            return this->getPluralityValue(exampleBitMap);
        }
        else
        {
            double entropyBefore = this->getInitialEntropy(exampleBitMap), infoGain, maxInfoGain = -DBL_MAX;
            int i = 0, selectedAttributeIndex = -1;
            for (char c : attributeBitMap)
            {
                if (c == '1')
                {
                    infoGain = entropyBefore - this->getRemainder(i, exampleBitMap);
                    if (infoGain > maxInfoGain)
                    {
                        selectedAttributeIndex = i;
                        maxInfoGain = infoGain;
                    }
                }
                i++;
            }

            assert(selectedAttributeIndex != -1);
            Node *rv = new Node();
            rv->setAttributeIndex(selectedAttributeIndex);
            attributeBitMap[selectedAttributeIndex] = '0';
            for (int j = 0; j < this->howManyValsPerAttr[selectedAttributeIndex]; j++)
            {
                i = 0;
                string newExampleBitMap = exampleBitMap;
                for (char c : exampleBitMap)
                {
                    if (c == '1' && this->trainingData[i][selectedAttributeIndex] != j)
                    {
                        newExampleBitMap[i] = '0';
                    }
                    i++;
                }
                rv->addChildren(this->learnByInfoGain(newExampleBitMap, attributeBitMap, exampleBitMap));
            }
            return rv;
        }

        cout << "should not happen\n";
        return NULL;
    }

    void learn()
    {
        string exampleBitMap(this->howManyExamples, '1');
        string attributeBitMap(this->howManyAttrs, '1');
        string parentExampleBitMap(this->howManyExamples, '1');
        this->root = learnByInfoGain(exampleBitMap, attributeBitMap, parentExampleBitMap);
    }

    int eval(const vector<int> &data)
    {
        string originalOutcome = this->goalClassValues[data.back()], evalOutcome;
        Node *test = this->root;
        while (test != NULL)
        {
            if (test->getAttributeIndex() == this->goalIndex)
            {
                evalOutcome = test->getOutcome();
                break;
            }
            else
            {
                test = test->getChildren()[data[test->getAttributeIndex()]];
            }
        }

        return (evalOutcome == originalOutcome) ? 1 : 0;
    }

    double evalTestData()
    {
        int correct = 0;
        for (auto data : this->testData)
        {
            correct += this->eval(data);
        }
        return (correct * 100.0 / this->testData.size());
    }

    void free()
    {
        delete this->root;
    }
};

int main(void)
{
    for (int i = 0; i < 20; i++)
    {
        DecisionTree d;
        d.feedData("car.data");
        d.learn();
        cout << "Accuracy : " << d.evalTestData() << '\n';
        d.free();
    }
    return 0;
}
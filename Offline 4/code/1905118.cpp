#include <bits/stdc++.h>
using namespace std;

class DecisionTree
{

private:
    int howManyAttrs, howManyExamples, goalIndex;
    vector<vector<int>> trainingData, testData; // training is actually examples
    vector<int> howManyValsPerAttr;

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
            multPart += ((double)x * myLog(x));
        }
        entropy = myLog(total) - (multPart / total);
        return entropy;
    }

public:
    DecisionTree(const DecisionTree &) = delete;

    DecisionTree()
    {
        this->howManyAttrs = this->howManyExamples = this->goalIndex = 0;
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
        
        for (int i = 0; i < tempData.size(); i++)
        {
            for (int j = 0; j < tempData[i].size(); j++)
            {
                replaceAttrValues.emplace_back(attrValMapper[{j, tempData[i][j]}]);
            }
            if(dist(gen) > 80) {
                this->testData.emplace_back(replaceAttrValues);
            }
            else {
                this->trainingData.emplace_back(replaceAttrValues);
            }
            replaceAttrValues.clear();
        }
       
        // assuming all examples have all attributes
        this->howManyExamples = this->trainingData.size();
        this->howManyAttrs = this->goalIndex = this->trainingData[0].size() - 1;
        this->howManyValsPerAttr.resize(this->howManyAttrs);
        cout << this->howManyExamples << ' ' << this->howManyAttrs << ' ' << this->goalIndex << '\n';
        for(int i = 0; i < this->howManyAttrs; i++) {
            this->howManyValsPerAttr[i] = attrValMapper2[i];
            cout << this->howManyValsPerAttr[i] << ' ';
        }
        inFile.close();
    }
};

int main(void)
{
    DecisionTree d;
    d.feedData("car.data");
    return 0;
}
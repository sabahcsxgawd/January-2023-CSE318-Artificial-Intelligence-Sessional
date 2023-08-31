#include <bits/stdc++.h>
using namespace std;

class DecisionTree
{

private:
    int howManyAttrs, howManyExamples, goalIndex;
    vector<vector<int>> howManyValsPerAttr, trainingData, testData; // training is actually examples

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
                if(attrValMapper.find({attrIndex, token}) == attrValMapper.end()) {
                    attrValMapper[{attrIndex, token}] = attrValMapper2[attrIndex]++;
                }
                attrIndex++;      
            }  
            ss.clear();
            tempData.emplace_back(tempAttrValues);
        }
        this->trainingData.clear();
        this->testData.clear();    
        for(int i = 0; i < tempData.size(); i++) {
            for(int j = 0; j < tempData[i].size(); j++) {
                replaceAttrValues.emplace_back(attrValMapper[{j, tempData[i][j]}]);
            }
            this->trainingData.emplace_back(replaceAttrValues);
            replaceAttrValues.clear();
        }

        for(auto x : this->trainingData) {
            for(int y : x) {
                cout << y << ' ';
            }
            cout << '\n';
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
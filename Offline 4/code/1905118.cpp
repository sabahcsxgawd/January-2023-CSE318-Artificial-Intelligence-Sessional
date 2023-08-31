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

    DecisionTree(const string &data)
    {
        // asssuming test data is in same folder with correct file name
        ifstream inFile(data);
        string line, token;
        stringstream ss;
        vector<string> tempAttrValues;
        map<pair<int, string>, int> attrValMapper;
        while (getline(inFile, line))
        {
            ss.str(line);
            this->howManyExamples++;
            tempAttrValues.clear();
            while (getline(ss, token, ','))
            {
                tempAttrValues.push_back(token);
                if (this->howManyExamples == 1)
                {
                    this->howManyAttrs++;
                    // TODO
                }
            }
        }
    }
};

int main(void)
{
    ifstream inFile("car.data");
    string line, token;
    stringstream ss;
    while (getline(inFile, line))
    {
        cout << line << '\n';
        ss.str(line);
        while (getline(ss, token, ','))
        {
            cout << token << '|';
        }
        break;
    }
    inFile.close();
    return 0;
}
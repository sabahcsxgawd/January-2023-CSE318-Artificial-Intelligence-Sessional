#include <bits/stdc++.h>
using namespace std;


bool isEmpty(const string &s) {
    for(char c : s) {
        if(c == '1') {
            return false;
        }
    }
    return true;
}

double myLog(double p) {
    if(p > 0.0) {
        return log2(p);
    }
    else {
        return 0.0;
    }
}

double getEntropy(const vector<int> &v) {
    double total, multPart, entropy;
    total = multPart = 0.0;
    for(int x : v) {
        total += (double)x;
        multPart += ((double)x * myLog(x));
    }
    entropy = myLog(total) - (multPart / total);
    return entropy;
}

int main(void) {
    ifstream inFile("car.data");
    string line, token;
    stringstream ss;
    while(getline(inFile, line)) {
        cout << line << '\n';        
        ss.str(line);
        while(getline(ss, token, ',')) {
            cout << token << '|';
        }
        break;
    }
    inFile.close();
    return 0;
}
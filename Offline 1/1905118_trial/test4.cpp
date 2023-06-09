#include<bits/stdc++.h>
using namespace std;

int main() {

    vector<vector<int>> v = {
        {4, 1, 3},
        {0, 2, 6},
        {7, 5, 8}
    };

    set<int>s;
    int inv = 0;
    for(int i=2;i>=0;i--) {
        for(int j=2;j>=0;j--) {
            if(v[i][j] != 0) {
                s.insert(v[i][j]);
                auto it = s.lower_bound(v[i][j]);
                cout << i << ' ' << j << ' ' << distance(s.begin(), it) << '\n';
            }
        }
    }

    return 0;
}
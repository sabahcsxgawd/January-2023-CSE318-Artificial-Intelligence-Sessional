#include<bits/stdc++.h>
using namespace std;

int main()
{
    vector<vector<int>> v1(2, vector<int> (2)), v2(2, vector<int> (2));
    v1[0][0] = 1;
    v1[0][1] = 2;
    v1[1][0] = 3;
    v1[1][1] = 4;
    
    v2[0][0] = 1;
    v2[0][1] = 2;
    v2[1][0] = 3;
    v2[1][1] = 4;
    
    
    if(v1 == v2) {
        cout << "gg\n";
    }
    else {
        cout << "rr\n";
    }

    return 0;
}
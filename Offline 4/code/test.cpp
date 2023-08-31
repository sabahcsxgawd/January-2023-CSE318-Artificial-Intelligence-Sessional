#include <bits/stdc++.h>
using namespace std;

int main(void) {
    map<pair<int, string>, int> mp;
    if(mp.find({1, "gege"}) == mp.end()) {
        mp[{1, "gege"}] = 0;
        cout << "gege0\n";
    }
    if(mp.find({1, "gege"}) == mp.end()) {
        mp[{1, "gege"}] = 10;
        cout << "gege10\n";
    }
    cout << mp[{1, "gege"}] << '\n';
    return 0;
}
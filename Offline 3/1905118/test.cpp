#include <bits/stdc++.h>
using namespace std;

int main() {
    pair<int, int> p = make_pair(1, 2);
    cout << p.first << ' ' << p.second << '\n';
    swap(p.first, p.second);
    cout << p.first << ' ' << p.second << '\n';
    return 0;
}
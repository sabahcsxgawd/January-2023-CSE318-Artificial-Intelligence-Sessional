#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pss pair<set<int>, set<int>>
#define pwpss pair<ll, pss>

int main() {
    // set<int> s1 = {1, 2, 3};
    // set<int> s2 = {4, 5, 6};
    // set<int> s3 = {1, 2, 3};
    // set<int> s4 = {7, 8, 9};
    // set<int> s5 = {13, 23, 33};
    // set<int> s6 = {14, 42, 3};

    // pss g1 = make_pair(s1, s2);
    // pss g2 = make_pair(s3, s4);
    // pss g3 = make_pair(s5, s6);

    // set<pwpss> s;
    // s.emplace(make_pair(20, g1));
    // s.emplace(make_pair(10, g2));
    // s.emplace(make_pair(30, g3));

    multiset<int> s;
    s.emplace(1);
    s.emplace(2);
    s.emplace(3);
    s.emplace(1);

    s.erase(s.begin());

    for(int x : s) {
        cout << x << ' ';
    }

    return 0;
}
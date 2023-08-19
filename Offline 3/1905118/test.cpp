#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(0, 1);


int main() {

    int zcnt = 0, ocnt = 0;

    for(int i = 0; i < 10; i++) {
        int p = dist(gen);
        if(p == 0) {
            zcnt++;
        }
        else if(p == 1) {
            ocnt++;
        }
    }

    assert((zcnt + ocnt) == 10);

    cout << zcnt * 1.0 / 10 << ' ' << ocnt * 1.0 / 10 << '\n';

    long long a = 10, b = 3;
    cout << a / b;

    return 0;
}
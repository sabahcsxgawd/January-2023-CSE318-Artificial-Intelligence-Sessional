#include<bits/stdc++.h>
using namespace std;


class A {

public:
    int a;
    double b;

};

void f(A* a) {
    a->a = 10;
    a->b = 3.3;
}

int main() {

    A a;
    f(&a);
    cout << a.a << " " << a.b << '\n';
    return 0;
}
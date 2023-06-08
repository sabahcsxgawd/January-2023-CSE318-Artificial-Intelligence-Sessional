#include <iostream>
#include <memory>
using namespace std;

class Node
{
public:
    shared_ptr<Node> parent;
    int val;

    Node(int val, shared_ptr<Node> parent)
    {
        this->val = val;
        this->parent = parent;
    }

};

int main()
{
    shared_ptr<Node> a(new Node(1, nullptr));
    shared_ptr<Node> b(new Node(2, a));
    shared_ptr<Node> c(new Node(3, a));

    return 0;
}
#include <string>
#include <iostream>
#include <climits>
#include <stack>

using namespace std;

class MinStack {
    public:
        MinStack() {}
        void push(int x);
        void pop();
        int top();
        int getMin();
    private:
        stack<pair<int, int>> stk;
};

void MinStack::push(int x)
{
    int min = INT_MAX;
    if (!stk.empty()) {
        const auto &top = stk.top();
        min = top.second;
    }
    if (min > x)
        min = x;
    pair<int, int> newTop{x, min};
    stk.push(newTop);   
}

void MinStack::pop()
{
    stk.pop();
}

int MinStack::top()
{
    return stk.top().first;
}

int MinStack::getMin()
{
    return stk.top().second;
}

int main(void)
{
    MinStack *minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    cout << minStack->getMin() << endl;    // --> Returns -3.
    minStack->pop();
    cout << minStack->top() << endl;       // --> Returns 0.
    cout << minStack->getMin() << endl;    // --> Returns -2.
    delete minStack;
    return 0;
}
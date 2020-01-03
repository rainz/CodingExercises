#include <iostream>
#include <vector>
#include <stack>
#include "utils.h"

using namespace std;
class ImplementQueueusingStacks {
    public:

    /** Initialize your data structure here. */
    ImplementQueueusingStacks() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        stk1.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (stk2.empty()) {
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        int n = stk2.top();
        stk2.pop();
        return n;
    }

    /** Get the front element. */
    int peek() {
        if (stk2.empty()) {
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        return stk2.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return stk1.empty() && stk2.empty();
    }

    private:
    // Remember you cannot transfer data from stk1 to stk2 unless stk2 is empty
    stack<int> stk1;
    stack<int> stk2;
};

int main(void)
{
    ImplementQueueusingStacks queue;
    queue.push(1);
    queue.push(2);
    cout << queue.peek() << endl;  // returns 1
    cout << queue.pop() << endl;   // returns 1
    cout << queue.empty() << endl; // returns false
    return 0;
}
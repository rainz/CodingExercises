#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> prevPermOpt1(vector<int>& A)
{
    stack<int> stk;
    for (int i = A.size()-1; i >= 0; --i) {
        if (i == A.size()-1 || A[i] <= A[stk.top()])
            stk.push(i);
        else {
            int exchangeIdx = -1;
            while (!stk.empty()) {
                int idx = stk.top();
                stk.pop();
                // Note the handling of equal case
                if (A[idx] < A[i] &&
                        (exchangeIdx == -1 || A[idx] != A[exchangeIdx]))
                    exchangeIdx = idx;
                else
                    break;
            }
            int tmp = A[i];
            A[i] = A[exchangeIdx];
            A[exchangeIdx] = tmp;
            break;
        }
    }
    return A;
}

int main(void)
{
    vector<int> input1 = {3,2,1};
    vector<int> result = prevPermOpt1(input1);
    for (auto i = 0; i < result.size(); ++i)
        cout << result[i] << ",";
    cout << endl;

    vector<int> input2 = {1,1,5};
    result = prevPermOpt1(input2);
    for (auto i = 0; i < result.size(); ++i)
        cout << result[i] << ",";
    cout << endl;
    
    vector<int> input3 = {1,9,4,6,7};
    result = prevPermOpt1(input3);
    for (auto i = 0; i < result.size(); ++i)
        cout << result[i] << ",";
    cout << endl;
    
    vector<int> input4 = {3,1,1,3};
    result = prevPermOpt1(input4);
    for (auto i = 0; i < result.size(); ++i)
        cout << result[i] << ",";
    cout << endl;
}
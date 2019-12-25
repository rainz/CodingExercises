#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.h"

using namespace std;

int numRescueBoats(vector<int>& people, int limit)
{
    sort(people.begin(), people.end());
    int result = 0;
    auto first = people.begin();
    auto last = people.end()-1;
    while (first <= last) {
        if (*first + *last <= limit)
            ++first;
        --last;
        ++result;
    }
    return result;
}


int main(void)
{
    vector<int> input1{1,2};
    vector<int> input2{3,2,2,1};
    vector<int> input3{3,5,3,4};
    cout << numRescueBoats(input1, 3) << endl;
    cout << numRescueBoats(input2, 3) << endl;
    cout << numRescueBoats(input3, 5) << endl;

    return 0;
}

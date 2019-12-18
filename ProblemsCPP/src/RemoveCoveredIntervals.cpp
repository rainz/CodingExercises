#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int removeCoveredIntervals(vector<vector<int>>& intervals) 
{
    sort(intervals.begin(), intervals.end(),
        [](const vector<int> &a, const vector<int> &b) {
            return a[0] != b[0] ? (a[0] < b[0]) : (a[1] < b[1]);
        });
    int result = 0;
    int maxEnd = -1;
    for (vector<int> &curr: intervals) {
        if (maxEnd < 0 || curr[1] > maxEnd) {
            ++result; // curr not covered by last
            maxEnd = curr[1];
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    vector<int> v1{1, 4};
    vector<int> v2{3, 6};
    vector<int> v3{2, 8};
    vector<vector<int>> input;
    input.push_back(v1);
    input.push_back(v2);
    input.push_back(v3);
    cout << removeCoveredIntervals(input) << endl;
    return 0;
}
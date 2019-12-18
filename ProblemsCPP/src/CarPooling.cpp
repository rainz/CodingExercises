#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool carPooling(vector<vector<int>>& trips, int capacity) {
        map<int, int> stations;
        for (int i = 0; i < trips.size(); ++i) {
            int count = trips[i][0];
            int begin = trips[i][1];
            int end = trips[i][2];
            auto it = stations.find(begin);
            int passengers = it != stations.end() ? it->second : 0;
            stations[begin] = passengers + count;
            it = stations.find(end);
            passengers = it != stations.end() ? it->second : 0;
            stations[end] = passengers - count;
        }
        for (auto &entry: stations) {
            capacity -= entry.second;
            if (capacity < 0)
                return false;
        }
        return true;
}

int main(void) {
    vector<int> v1_1 = {2,1,5};
    vector<int> v1_2 = {3,3,7};
    vector<vector<int>> input1;
    input1.push_back(v1_1);
    input1.push_back(v1_2);
    cout << (carPooling(input1, 4)) << endl;

    vector<int> v2_1 = {2,1,5};
    vector<int> v2_2 = {3,3,7};
    vector<vector<int>> input2;
    input2.push_back(v2_1);
    input2.push_back(v2_2);
    cout << (carPooling(input2, 5)) << endl;

    vector<int> v3_1 = {2,1,5};
    vector<int> v3_2 = {3,5,7};
    vector<vector<int>> input3;
    input3.push_back(v3_1);
    input3.push_back(v3_2);
    cout << (carPooling(input3, 3)) << endl;

    vector<int> v4_1 = {3,2,7};
    vector<int> v4_2 = {3,7,9};
    vector<int> v4_3 = {8,3,9};
    vector<vector<int>> input4;
    input4.push_back(v4_1);
    input4.push_back(v4_2);
    input4.push_back(v4_3);
    cout << (carPooling(input4, 11)) << endl;
}
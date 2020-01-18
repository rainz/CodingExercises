#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "utils.h"

using namespace std;

vector<vector<int>> highFive(vector<vector<int>>& items)
{
    map<int, priority_queue<int, vector<int>, greater<int>>> students;
    for (const auto &item: items) {
        int id = item[0];
        int score = item[1];
        auto &pq = students[id];
        pq.push(score);
        if (pq.size() > 5)
            pq.pop();
    }
    vector<vector<int>> ans;
    for (auto it = students.cbegin(); it != students.cend(); ++it) {
        auto pq = it->second;
        int scoreCount = pq.size();
        int sum = 0;
        while (!pq.empty()) {
            sum += pq.top();
            pq.pop();
        }
        ans.emplace_back(vector<int>());
        ans.back().push_back(it->first);
        ans.back().push_back(sum/scoreCount);
    }
    return ans;
}

int main(void)
{
    vector<vector<int>> v1{{1,91},{1,92},{2,93},{2,97},{1,60},{2,77},{1,65},{1,87},{1,100},{2,100},{2,76}};
    printVector2D(highFive(v1));
    return 0;
}
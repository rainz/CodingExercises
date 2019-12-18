#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int maxDistance(vector<vector<int>>& grid)
{
    int rows = grid.size();
    if (rows == 0)
        return -1;
    int cols = grid[0].size();
    int dirs[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    int maxDist = -1; // if there's no land or all lands, return this.
    int distance[rows][cols];
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            distance[r][c] = INT_MAX;
    
    queue<pair<int, int>> workQ;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 1) {
                workQ.push(make_pair(r, c));
                distance[r][c] = 0;
            }
        }
    }

    while (!workQ.empty()) {
        pair<int, int> cell = workQ.front();
        workQ.pop();
        int r = cell.first;
        int c = cell.second;
        for (int i = 0; i < sizeof(dirs)/sizeof(dirs[0]); ++i) {
            int newR = r + dirs[i][0];
            if (newR < 0 || newR >= rows)
                continue;
            int newC = c + dirs[i][1];
            if (newC < 0 || newC >= cols)
                continue;
            if (grid[newR][newC] == 1)
                continue; // no need to queue this land cell again
            int newDist = distance[r][c] + 1;
            if (newDist < distance[newR][newC]) {
                distance[newR][newC] = newDist;
                if (newDist > maxDist)
                    maxDist = newDist;
                workQ.push(make_pair(newR, newC));
            }
        }
    }
    return maxDist;
}


int main(void)
{
    vector<int> v11{1,0,1};
    vector<int> v12{0,0,0};
    vector<int> v13{1,0,1};
    vector<vector<int>> input1;
    input1.push_back(v11);
    input1.push_back(v12);
    input1.push_back(v13);
    cout << maxDistance(input1) << endl;
    vector<int> v21{1,0,0};
    vector<int> v22{0,0,0};
    vector<int> v23{0,0,0};
    vector<vector<int>> input2;
    input2.push_back(v21);
    input2.push_back(v22);
    input2.push_back(v23);
    cout << maxDistance(input2) << endl;
    return 0;
}
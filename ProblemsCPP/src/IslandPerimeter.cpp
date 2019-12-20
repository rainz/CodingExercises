#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include "utils.h"

using namespace std;

int islandPerimeter(vector<vector<int>>& grid) {
    int rows = grid.size();
    if (rows == 0)
        return 0;
    int cols = grid[0].size();
    pair<int, int> start;
    bool found = false;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 1) {
                start.first = r;
                start.second = c;
                found = true;
                break;
            }
        }
        if (found)
            break; // need to break again out of outer loop
    }
    if (!found)
        return 0;

    int dirs[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int result = 0;
    bool visited[rows][cols];
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int>> workQ;
    workQ.push(start);
    while (!workQ.empty()) {
        auto cell = workQ.front();
        workQ.pop();
        int r = cell.first;
        int c = cell.second;
        if (visited[r][c])
            continue;
        for (int i = 0; i < 4; ++i) {
            int newR = r + dirs[i][0];
            int newC = c + dirs[i][1];
            if (newR < 0 || newR >= rows || newC < 0 || newC >= cols) {
                ++result; // out of bound
                continue;
            }
            if (grid[newR][newC] == 0) {
                ++result; // water
                continue;
            }
            workQ.push(make_pair(newR, newC));
        }
        visited[r][c] = true;
    }
    return result;
}


int main(void)
{
    int input[][4] = {{0,1,0,0},
                      {1,1,1,0},
                      {0,1,0,0},
                      {1,1,0,0}};
    vector<vector<int>> v2d;
    buildVector2D(v2d, (int*)input, 4, 4);
    cout << islandPerimeter(v2d) << endl;

    int input2[][2] = {{1,1},{1,1}};
    vector<vector<int>> v2d2;
    buildVector2D(v2d2, (int*)input2, 2, 2);
    cout << islandPerimeter(v2d2) << endl;
}
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include "utils.h"

using namespace std;

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor)
{
    int dirs[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int rows = image.size();
    if (rows == 0)
        return image;
    int cols = image[0].size();
    bool visited[rows][cols];
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int>> workQ;
    int startColor = image[sr][sc];
    workQ.push(make_pair(sr, sc));
    while (!workQ.empty()) {
        auto cell = workQ.front();
        workQ.pop();
        int r = cell.first;
        int c = cell.second;
        image[r][c] = newColor;
        visited[r][c] = true;
        for (int i = 0; i < 4; ++i) {
            int newR = r + dirs[i][0];
            int newC = c + dirs[i][1];
            if (newR >= 0 && newR < rows &&
                newC >= 0 && newC < cols &&
                !visited[newR][newC] &&
                image[newR][newC] == startColor)
            {
                workQ.push(make_pair(newR, newC));
            }
        }
    }
    return image;
}

int main(void)
{
    int input[][3] = {{1,1,1},{1,1,0},{1,0,1}};
    vector<vector<int>> v2d;
    buildVector2D(v2d, (int*)input, 3, 3);
    printVector2D(floodFill(v2d, 1,1, 2));
}
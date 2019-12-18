#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int maxEqualRowsAfterFlips(vector<vector<int>>& matrix)
{
    int rows = matrix.size();
    if (rows == 0)
        return 0;
    int cols = matrix[0].size();
    unordered_map<string, int> freqs;
    int result = 0;
    char buffer1[cols];
    char buffer2[cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            buffer1[j] = '0' + matrix[i][j];
            buffer2[j] = '0' + 1 - matrix[i][j];
        }
        string key(buffer1, cols);
        int freq = freqs[key];
        ++freq;
        if (freq > result)
            result = freq;
        freqs[key] = freq;

        string key2(buffer2, cols);
        freq = freqs[key2];
        ++freq;
        if (freq > result)
            result = freq;
        freqs[key2] = freq;
    }
    return result;
}

int main (void)
{
    vector<int> v1_1{0,1};
    vector<int> v1_2{1,1};
    vector<vector<int>> v1;
    v1.push_back(v1_1);
    v1.push_back(v1_2);
    cout << maxEqualRowsAfterFlips(v1) << endl;

    vector<int> v2_1{0,1};
    vector<int> v2_2{1,0};
    vector<vector<int>> v2;
    v2.push_back(v2_1);
    v2.push_back(v2_2);
    cout << maxEqualRowsAfterFlips(v2) << endl;

    vector<int> v3_1{0,0,0};
    vector<int> v3_2{0,0,1};
    vector<int> v3_3{1,1,0};
    vector<vector<int>> v3;
    v3.push_back(v3_1);
    v3.push_back(v3_2);
    v3.push_back(v3_3);
    cout << maxEqualRowsAfterFlips(v3) << endl;
}
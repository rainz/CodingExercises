#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;


int main() {
    string homepath = getenv("HOME");
    string filepath = homepath + "/test.txt";
    ifstream fin(filepath);
    int nCount, qCount;
    string line;
    getline(fin, line);
    istringstream iss1(line);
    iss1 >> nCount >> qCount;
    unordered_map<string, unordered_map<string, string>> kvs;
    string full_tag_name;
    for (int i = 0; i < nCount; ++i) {
        getline(fin, line);
        int idx = line.rfind('>');
        line.resize(idx); // get rid of >
        istringstream iss(line);
        if (line[1] == '/') { // closing tag
            idx = full_tag_name.rfind('.');
            if (idx < 0)
                full_tag_name = "";
            else
                full_tag_name.resize(idx);
            continue;
        }
        iss.get(); // skip <
        string tag_name;
        iss >> tag_name;
        if (full_tag_name.length() == 0)
            full_tag_name = tag_name;
        else {
            full_tag_name += '.';
            full_tag_name += tag_name;
        }
        auto &attrs = kvs[full_tag_name];
        string k, eq, v;
        while (!iss.eof()) {
            iss >> k >> eq >> v;
            string val = v.substr(1, v.length()-2); // strip off quotes
            attrs[k] = val;
        }
    }
    
    for (int i = 0; i < qCount; ++i) {
        string line;
        getline(fin, line);
        int idx = line.find('~');
        string tag = line.substr(0, idx);
        string k = line.substr(idx+1);
        auto it = kvs.find(tag);
        if (it == kvs.end())
            cout << "Not Found!" << endl;
        else {
            auto it2 = it->second.find(k);
            if (it2 == it->second.end())
                cout << "Not Found!" << endl;
            else
                cout << kvs[tag][k] << endl;
        }
    }
    return 0;
}

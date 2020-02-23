#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm> 
#include <functional>
#include "utils.h"

using namespace std;

struct TestObj {
    int aField;
    int bField;
    TestObj(int a, int b) : aField(a), bField(b) {}
};

bool lessMod(int x, int y) {
    return x % 3 < y % 3;
}

template <int MOD>
struct MyFunctor {
public:
    bool operator()(int x, int y) {
        return x % MOD < y % MOD;
    }
};

struct MyCmpFunctor {
public:
    bool operator()(const TestObj& x, const TestObj& y) {
        return x.bField < y.bField;
    }
};

void testSorting()
{
    // Note: without a comparator, sort uses "<" operator.
    // So you can override the "<" operator of a class

    MyFunctor<3> ftr;
    int arr[] = {9,8,7,6,5,14,13,12,11,10};
    int modVal = 5;
    auto cmp = [](auto x, auto y){ return x.aField < y.aField; };

    // Array sorting
    // sort(arr, arr+3); // sorts first 3
    // sort(begin(arr), end(arr)); // entire array sorted
    // sort(begin(arr), end(arr), greater<int>()); // sorted in reverse. Note the "()" after greater<int>
    // sort(rbegin(arr), rend(arr)); // sorted in reverse
    // sort(rbegin(arr), rbegin(arr)+6); // *last* 6 sorted in reverse
    // sort(begin(arr), begin(arr)+4); // sorts firt 4
    // sort(begin(arr), end(arr), lessMod); // sort by function
    // sort(begin(arr), end(arr), ftr); // sort by functor
    // sort(begin(arr), end(arr), [](auto x, auto y){return x % 5 < y % 5;}); // sort by lambda
    // sort(begin(arr), end(arr), [&](auto x, auto y){return x % modVal < y % modVal;}); // sort by lambda with capture by ref
    // sort(begin(arr), end(arr), [=](auto x, auto y){return x % modVal < y % modVal;}); // sort by lambda with capture by val
    // printArray(arr, sizeof(arr)/sizeof(arr[0]));

    // Vector sorting: similar to array sorting, use v.begin()/v.end() instead of begin(arr)/end(arr)
    // vector<int> v(begin(arr), end(arr));
    //sort(v.begin(), v.begin()+4, ftr); // sort first 4 with functor
    // printVector(v);

    // Map with comparators
    // map<TestObj, int, MyCmpFunctor> treeMap; // using functor, can't use function
    // map<TestObj, int, decltype(cmp)> treeMap(cmp); // using lambda
    // for (int i: arr) {
    //     TestObj obj(i, 100-i);
    //     treeMap[obj] = i*i;
    // }
    // for (auto it = treeMap.cbegin(); it != treeMap.cend(); ++it)
    //     cout << it->first.aField << "-" << it->first.bField << ": " << it->second << endl;

    // Set with comparators
    // set<TestObj, MyCmpFunctor> treeSet; // using functor, can't use function
    // set<TestObj, decltype(cmp)> treeSet(cmp); // using lambda
    // for (int i: arr) {
    //     TestObj obj(i, 100-i);
    //     treeSet.insert(obj);
    // }
    // for (auto it = treeSet.cbegin(); it != treeSet.cend(); ++it)
    //     cout << it->aField << "-" << it->bField << endl;

    // PQ with comparators
    // priority_queue<TestObj, vector<TestObj>, MyCmpFunctor> pq; // using functor
    // priority_queue<TestObj, vector<TestObj>, decltype(cmp)> pq(cmp); // using lambda
    // for (int i: arr) {
    //     TestObj obj(i, 100-i);
    //     pq.push(obj);
    // }
    // while (!pq.empty()) {
    //     auto &x = pq.top();
    //     cout << x.aField << "-" << x.bField << endl;
    //     pq.pop();
    // }

}

void testRef()
{
    vector<int> v1, v2;
    vector<int>& ref = v1;
    v1.push_back(11);
    v1.push_back(12);
    v2.push_back(21);
    v2.push_back(22);
    cout << "v1: ";
    for (auto it = v1.begin(); it != v1.end(); ++it)
        cout << *it << ",";
    cout << endl;
    ref = v2; // this actually assigned v2 to v1 !!!!!! 
    ref.push_back(999); // appended to v1 !!! v2 not changed !!!
    cout << "v1 after ref assign: ";
    for (auto it = v1.begin(); it != v1.end(); ++it)
        cout << *it << ",";
    cout << endl;
    cout << "v2 after ref assign: ";
    for (auto it = v2.begin(); it != v2.end(); ++it)
        cout << *it << ",";
    cout << endl;
}

void testMove()
{
    vector<int> v1{1,2,3,4,5};
    vector<int> v2{10,20};
    v2 = move(v1);
    printVector(v1);
    printVector(v2);
}

void testFile()
{
    string homepath = getenv("HOME");
    string filepath = homepath + "/text.txt";
    cerr << "Opening " << filepath << endl;
    ifstream infile;
    infile.open(filepath);
    if (!infile) {
        cerr << "bad file" << endl;
        return;
    }
    ofstream outfile;
    outfile.open(homepath + "/out.txt");
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string field;
        while (getline(iss, field, ','))
            outfile << field << "|";
        outfile << endl;
    }
    infile.close();
    outfile.close();
}

int main(void)
{
    //testSorting();
    testRef();
    //testMove();
    //testFile();
    return 0;
}
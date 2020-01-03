#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class InsertDeleteGetRandomO1 {
private:
    unordered_map<int, int> numsTable;
    vector<int> numsArray;

public:
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (numsTable.find(val) != numsTable.end())
            return false;
        numsArray.push_back(val);
        numsTable[val] = numsArray.size() - 1;
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (numsTable.find(val) == numsTable.end())
            return false;
        int removeIdx = numsTable[val];
        // Copy last value to removeIdx in arraylist and resize
        int lastIdx = numsArray.size() - 1;
        int lastVal = numsArray[lastIdx];
        numsArray[removeIdx] = lastVal;
        numsArray.resize(lastIdx); // remove last item
        numsTable[lastVal] = removeIdx; // do this before removing val, because lastVal might equal val
        numsTable.erase(val);
        return true;
    }

    /** Get a random element from the set. */
    int getRandom() {
        return numsArray[rand() % numsArray.size()];
    }
};

int main(void)
{
    InsertDeleteGetRandomO1 *randomSet = new InsertDeleteGetRandomO1();
    /*
    cout << randomSet->insert(1) << endl;
    cout << randomSet->remove(2) << endl;
    cout << randomSet->insert(2) << endl;
    cout << randomSet->getRandom() << endl;
    cout << randomSet->remove(1) << endl;
    cout << randomSet->insert(2) << endl;
    cout << randomSet->getRandom() << endl;
    */
    cout << randomSet->remove(0) << endl;
    cout << randomSet->remove(0) << endl;
    cout << randomSet->insert(0) << endl;
    cout << randomSet->getRandom() << endl;
    cout << randomSet->remove(0) << endl;
    cout << randomSet->insert(0) << endl;
    delete randomSet;
    return 0;
}

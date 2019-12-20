#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.h"

using namespace std;

int carFleet(int target, vector<int>& position, vector<int>& speed)
{
    vector<pair<int, int>> cars;
    for (int i = 0; i < position.size(); ++i) {
        cars.push_back(make_pair(position[i], speed[i]));
    }
    // Sort by position, furthest first
    sort(cars.rbegin(), cars.rend());

    vector<pair<int, int>> fleets;
    for (auto car: cars) {
        if (fleets.empty()) {
            fleets.push_back(car);
            continue;
        }
        auto prevFleet = fleets[fleets.size()-1];
        int speedDiff = car.second - prevFleet.second;
        if (speedDiff > 0) {
            double distDiff = prevFleet.first - car.first;
            double prev2Target = target - prevFleet.first;
            if (distDiff/speedDiff <= prev2Target/prevFleet.second) {
                // This car will catch up the previous fleet
                continue;
            }
        }
        // Can't catch up. This will be a new fleet
        fleets.push_back(car);
    }
    return fleets.size();
}

int main(void)
{
    vector<int> positions1{10,8,0,5,3};
    vector<int> speeds1{2,4,1,1,3};
    cout << carFleet(12, positions1, speeds1) << endl;
    return 0;
}
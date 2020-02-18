#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <functional>
#include "utils.h"

using namespace std;

int gcd(int num1, int num2) {
    while (num1 != num2) {
        if(num1 > num2)
            num1 = num1 - num2;
        else
            num2 = num2 - num1;
    }
    return num2;
}

void testPrimeFactors()
{
    //int num = 2*2*3*5*5*7*7;
    //int num = 19;
    //int num = 3*5*5*7*7*19;
    int num = 2;

    vector<int> factors;
    int n = num;
    for (int i = 2; i*i <= n; ++i) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1)
        factors.push_back(n);

    cout << "Factors of " << num << ": " << endl;
    printVector(factors);
}

void getDivisors(int num, vector<int> &divisors) {
    for (int i = 1; i*i <= num; ++i) {
        if (num % i == 0) {
            divisors.push_back(i);
            if (i != num/i)
                divisors.push_back(num/i);
        }
    }
}

void testDivisors(int num) {
    vector<int> divisors;
    getDivisors(num, divisors);
    int sum = accumulate(divisors.begin(), divisors.end(), 0) - num;
    cout << "Divsiors of " << num << ": " << endl;
    printVector(divisors);
    cout << "Sum of divisors: " << sum << endl;
}

void divisorPairs() {
    int N = 300;
    unordered_map<int, int> divisorMap;
    for (int n = 2; n < N; ++n) {
        vector<int> divisors;
        getDivisors(n, divisors);
        int sum = accumulate(divisors.begin(), divisors.end(), 0) - n;
        divisorMap[n] = sum;
    }
    for (auto it = divisorMap.begin(); it != divisorMap.end(); ++it) {
        int n = it->first;
        int sum = it->second;
        if (n != sum && divisorMap.count(sum) > 0 && divisorMap.at(sum) == n)
            cout << "Pair: " << n << ", " << sum << endl;
    }
}

int main(void)
{
    //testPrimeFactors();
    testDivisors(284);
    testDivisors(220);
    //divisorPairs();
    return 0;
}
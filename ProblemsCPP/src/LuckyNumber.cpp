/*
 * LuckyNumber.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: Yu
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

const static int MAX_DIGITS = 18;

static int max_prime_idx = 0; // index of max prime for digits sum
vector<int> all_primes;

static void findPrimes(int max_prime_digit, int n, vector<int>& primes)
{
  vector<int> sieve;
  for (int i = 2; i <= n; ++i) {
    sieve.push_back(i);
  }

  size_t idx = 0;
  while (idx < sieve.size()) {
    int prim = sieve[idx];
    primes.push_back(prim);

    // Keep track of the max prime index for digits sum
    if (prim <= max_prime_digit)
      max_prime_idx = primes.size() - 1;

    size_t sieve_idx = idx + prim;
    while (sieve_idx < sieve.size()) {
      sieve[sieve_idx] = 0;
      sieve_idx += prim;
    }
    do {
      ++idx;
    } while (idx < sieve.size() && sieve[idx] == 0);
  }

}

typedef vector<int> DigitsCount;
typedef multimap<int, DigitsCount> DigitSums;
typedef map<int, DigitSums> DigitSumMap;
DigitSumMap digitSumMap;

static int numDigits(const DigitsCount& digits_count, int& sum, int& square_sum)
{
  int num = 0;
  sum = 0;
  square_sum = 0;
  for (size_t i = 0; i < digits_count.size(); ++i) {
    int count = digits_count[i];
    num += count;
    int same_digit_sum = count*i;
    sum += same_digit_sum;
    square_sum += same_digit_sum*i;
  }
  return num;
}

static void saveComboAnswer(const DigitsCount& digits_count)
{
  int prime, square_prime;
  int num_digits = numDigits(digits_count, prime, square_prime);
  // Check if square sum is a prime.
  if (!binary_search(all_primes.begin(), all_primes.end(), square_prime))
    return;

  DigitSums& ds = digitSumMap[prime];
  if (num_digits > MAX_DIGITS)
    cerr << "ERROR: number too long:" << num_digits << endl;

  /*
  cout << "prime=" << prime << ",sq_prime=" << square_prime << ",num_digits=" << num_digits << ':';
  for (size_t i = 1; i < digits_count.size(); ++i) {
    if (digits_count[i] > 0)
      cout << i << '*' << digits_count[i] << '+';
  }
  cout << endl;
  */
  ds.insert(pair<int, DigitsCount>(num_digits, digits_count));

  // Add this digits_count with all possible 0's
  /*
  for (int num = num_digits; num <= MAX_DIGITS; ++num) {
    pair<int, DigitsCount> tmp_dc(num, digits_count);
    tmp_dc.second[0] = num - num_digits;
    ds.insert(tmp_dc);
  }
  */

}

static void findDigitsWithSum(int sum, int len, int digit, DigitsCount& digits_count)
{
  if (sum <= 0) {
    saveComboAnswer(digits_count);
    return;
  }

  if (digit > 9)
    return;

  if (sum > len*9) {
    return; // sum too large for the rest of the digits
  }

  int old_count = digits_count[digit];
  int max_count = sum/digit;
  for (int count = old_count; count <= max_count; ++count) {
    int picked = count - old_count;
    if (picked > len)
      break;
    digits_count[digit] = count;
    findDigitsWithSum(sum-count*digit, len-picked, digit+1, digits_count);
  }
  digits_count[digit] = old_count;
}

static int countDigits(unsigned long long x)
{
  int count = 0;
  while (x > 0LL) {
    x /= 10LL;
    ++count;
  }
  return count;
}

int luckyNumberMain()
{
  //cout << numeric_limits<unsigned long long>::max() << endl;

  findPrimes(18*9, 18*81, all_primes);
  //cout << "Primes count:" << all_primes.size() << ", for digit sum: " << max_prime_idx << endl;

  DigitsCount digits_count(10, 0);
  for (int i = 0; i <= max_prime_idx; ++i) {
    int prime = all_primes[i];
    findDigitsWithSum(all_primes[i], MAX_DIGITS, 1, digits_count);
    const DigitSums &ds = digitSumMap[prime];
    //cout << all_primes[i] << ':' << ds.size() << endl;
  }

  /*
  int num_tests;
  cin >> num_tests;
  for (int i = 0; i < num_tests; ++i) {
    unsigned long long A, B;
    cin >> A >> B;
    int a_count = countDigits(A);
    int b_count = countDigits(B);

  }
 */
  return 0;
}

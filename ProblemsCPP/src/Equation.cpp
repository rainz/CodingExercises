#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

void findPrimesBrute(int n, vector<int>& primes)
{
  primes.push_back(2);

  for (int i = 3; i <= n; i += 2) {
    int n_sqrt = (int)sqrt(i);
    bool isPrime = true;
    for (size_t idx = 0; idx < primes.size(); ++idx) {
      int factor = primes[idx];
      if (factor > n_sqrt)
        break;
      if (i % factor == 0) {
        isPrime = false;
        break;
      }
    }
    if (isPrime)
      primes.push_back(i);
  }
}

static void findPrimes(int n, vector<int>& primes)
{
  vector<int> sieve;
  for (int i = 2; i <= n; ++i) {
    sieve.push_back(i);
  }

  size_t idx = 0;
  while (idx < sieve.size()) {
    int prim = sieve[idx];
    primes.push_back(prim);
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

unsigned long long computeExponent(unsigned long long n, unsigned long long prime)
{
  unsigned long long exp = 0;
  unsigned long long factor = prime;
  while (factor <= n) {
    exp += n / factor;
    factor *= prime;
  }
  return exp;
}

static int runTest()
{
  cout << computeExponent(1000000, 2) << endl;
  return 0;
}

int equationMain(void)
{
  //return runTest();

  static const unsigned long long MODULO = 1000007LL;
  int N;
  cin >> N;

  unsigned long long total = 1;

  vector<int> primes;
  findPrimes(N, primes);
  //cout << primes.size() << " primes under " << N << endl;
  for (size_t idx = 0; idx < primes.size(); ++idx) {
    unsigned long long exp = (computeExponent(N, primes[idx])*2 + 1) % MODULO;
    total = (total * exp) % MODULO;
    //cout << "prime:" << primes[idx] << ", exp:" << exp << endl;
  }

  cout << total << endl;


  return 0;
}

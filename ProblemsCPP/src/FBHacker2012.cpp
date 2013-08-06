/*
 * FBHacker2012.cpp
 *
 *  Created on: Jan 21, 2012
 *      Author: Yu
 */

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cassert>

#include "utils.h"

using namespace std;

const int ALPHA_BITMAP_SIZE = 26;
void buildAlphabetBitmap(const string& phrase, short* bitmap)
{
  memset(bitmap, 0, ALPHA_BITMAP_SIZE*sizeof(short));
  const size_t phrase_len = phrase.length();
  //cout << phrase << endl;
  for (size_t i = 0; i < phrase_len; ++i) {
    if (phrase[i] < 'A' || phrase[i] > 'Z')
      continue;
    ++bitmap[phrase[i]-'A'];
  }
  /*
  for (size_t i = 0; i < ALPHA_BITMAP_SIZE; ++i)
    if (bitmap[i] > 0)
      cout << (char)('A'+i) << ": " << (unsigned)bitmap[i] << ", ";
  cout << endl;
  */
}

int FBHackerAlphabetSoup()
{
  const string PHRASE = "HACKERCUP";
  const int PHRASE_LEN = PHRASE.length();
  short phrase_bitmap[ALPHA_BITMAP_SIZE];
  buildAlphabetBitmap(PHRASE, phrase_bitmap);

  string num_tests_str;
  getline(cin, num_tests_str);
  int num_tests = atoi(num_tests_str.c_str());
  short test_bitmap[ALPHA_BITMAP_SIZE];
  for (int i = 0; i < num_tests; ++i) {
    string line_str;
    getline(cin, line_str);
    buildAlphabetBitmap(line_str, test_bitmap);
    int min_multiple = INT_MAX;
    for (int j = 0; j < PHRASE_LEN; ++j) {
      const int c = PHRASE[j] - 'A';
      int multiple = (int)test_bitmap[c] / (int)phrase_bitmap[c];
      if (multiple < min_multiple)
        min_multiple = multiple;
    }
    cout << "Case #" << i+1 << ": " << min_multiple << endl;
  }
  return 0;
}

bool canFitBillboard(const vector<string>& strs, size_t font_size, size_t width, size_t height)
{
  assert(font_size > 0);

  size_t curr_height = font_size, curr_width = 0;
  const size_t strs_count = strs.size();
  for (size_t i = 0; i < strs_count; ++i) {
    size_t str_width = strs[i].length()*font_size;
    if (str_width > width)
      return false; // word too wide
    if (curr_width == 0)
      curr_width += str_width;
    else
      curr_width += str_width + font_size; // must include a space
    if (curr_width > width) {
      curr_width = str_width;
      curr_height += font_size;
    }
    if (curr_height > height)
      return false;
  }

  return true;
}

int FBHackerBillboards()
{
  string num_tests_str;
  getline(cin, num_tests_str);
  int num_tests = atoi(num_tests_str.c_str());
  for (int test_idx = 0; test_idx < num_tests; ++test_idx) {
    string line_str;
    getline(cin, line_str);
    vector<string> test_strings;
    tokenize(line_str, test_strings, ' ');
    int width = atoi(test_strings[0].c_str());
    int height = atoi(test_strings[1].c_str());
    test_strings.erase(test_strings.begin());
    test_strings.erase(test_strings.begin());

    size_t top_size = min(width, height), bottom_size = 0;
    // Binary search of font size
    size_t mid_size;
    while (top_size >= bottom_size) {
      if (top_size - bottom_size <= 1)
        mid_size = top_size;
      else
        mid_size = (top_size + bottom_size) / 2;
      if (canFitBillboard(test_strings, mid_size, width, height)) {
        bottom_size = mid_size;
        if (bottom_size == top_size)
          break;
      }
      else {
        top_size = mid_size;
        if (bottom_size == top_size - 1)
          break;
      }
    }

    cout << "Case #" << test_idx+1 << ": " << bottom_size << endl;
  }
  return 0;
}

struct Product {
  unsigned price;
  unsigned weight;

  bool isBargain;
  bool isTerrible;

  long long idx;

  bool isBetterThan(const Product& other) const
  {
    return ( (price < other.price && weight <= other.weight) ||
             (price <= other.price && weight < other.weight)
           );
  }

  void nextProduct(int M, int K, int A, int B, int C, int D)
  {
    price = ((A*price + B) % M) + 1;
    weight = ((C*weight + D) % K) + 1;
    isBargain = true;
    isTerrible = true;
    ++idx;
  }

  Product(unsigned p, unsigned w) : price(p), weight(w), isBargain(true), isTerrible(true), idx(1)
  {
  }

  bool operator==(const Product& other) const
  {
    return (price == other.price && weight == other.weight);
  }

  bool operator<(const Product& other) const
  {
    return (idx < other.idx);
  }

};

void bruteForce(long long N, int P1, int W1, int M, int K, int A, int B, int C, int D, int &bargain_count, int &terrible_count)
{
  typedef vector<Product> Products;
  Products products;
  Product prod(P1, W1);
  products.push_back(prod);
  bargain_count = 0;
  terrible_count = 0;
  //cout << '(' << prod.price << ',' << prod.weight << ')' << endl;
  for (long long i = 2; i <= N; ++i) {
    prod.nextProduct(M, K, A, B, C, D);
    products.push_back(prod);
  }

  for (long long i = 0; i < N; ++i) {
    bool foundBetterThanMe = false, foundWorseThanMe = false;
    const Product &prod = products[i];
    for (long long j = 0; j < N; ++j) {
      if (i == j)
        continue;
      const Product &other = products[j];
      if (!foundWorseThanMe && prod.isBetterThan(other))
        foundWorseThanMe = true;
      if (!foundBetterThanMe && other.isBetterThan(prod))
        foundBetterThanMe = true;
      if (foundWorseThanMe && foundBetterThanMe)
        break;
    }
    if (!foundBetterThanMe)
      ++bargain_count;
    if (!foundWorseThanMe)
      ++terrible_count;
  }
}

enum {
  BARGAIN = 0,
  TERRIBLE = 1
};

struct ProdStats {
  long long cycle_start;
  long long cycle_end; // excludes the last one
  long long cycle_partial_end; // excludes the last one
  long long N;

  enum {
    PRE_CYCLE = 0,
    CYCLE = 1,
    PARTIAL = 2
  };

  long long stats[3][2]; // 3 stages, 2 types (bargain & terrible)

  ProdStats(long long n) : N(n)
  {
    memset(stats, 0, sizeof(stats));
  }

  void updateStats(long long idx, int increment, int type)
  {
    if (idx < cycle_start)
      stats[PRE_CYCLE][type] += increment;
    else {
      stats[CYCLE][type] += increment;
      if (idx < cycle_partial_end)
        stats[PARTIAL][type] += increment;
    }
  }

  long long getCount(int type)
  {
    return stats[PRE_CYCLE][type] + stats[PARTIAL][type] + stats[CYCLE][type]*((N-cycle_start+1)/(cycle_end-cycle_start));
  }
};

void findCycle(long long N, int P1, int W1, int M, int K, int A, int B, int C, int D, ProdStats &stats)
{
  Product prod(P1, W1);
  typedef map<pair<int, int>, long long> ProductMap;
  ProductMap prod_map;
  prod_map[make_pair(P1, W1)] = 1;
  for (long long i = 2; i <= N; ++i) {
    prod.nextProduct(M, K, A, B, C, D);
    pair<int, int> pw_pair(prod.price, prod.weight);
    ProductMap::const_iterator it = prod_map.find(pw_pair);
    if (it != prod_map.end()) {
      stats.cycle_start = it->second;
      stats.cycle_end = i;
      long long cycle_partial_len = (N - stats.cycle_start + 1) % (stats.cycle_end - stats.cycle_start);
      stats.cycle_partial_end = stats.cycle_start + cycle_partial_len; // cycle_partial_end excludes the last one
      //cout << "cycle found: " << stats.cycle_start << " to " << stats.cycle_end << ", partial end " << stats.cycle_partial_end << endl;
      return;
    }
    prod_map[pw_pair] = i;
  }
  stats.cycle_start = 1;
  stats.cycle_end = N + 1;
  stats.cycle_partial_end = 1;
  //cout << "No cycle found" << endl;
}


int FBHackerAuction()
{
  int num_tests;
  cin >> num_tests;
  for (int test_idx = 0; test_idx < num_tests; ++test_idx) {
    long long N;
    int P1, W1, M, K, A, B, C, D;
    cin >> N >> P1 >> W1 >> M >> K >> A >> B >> C >> D;
    ProdStats stats(N);
    findCycle(N, P1, W1, M, K, A, B, C, D, stats);
    typedef list<Product> Products;
    Products products;
    Product prod(P1, W1);
    products.push_front(prod);
    stats.updateStats(prod.idx, 1, BARGAIN);
    stats.updateStats(prod.idx, 1, TERRIBLE);
    //cout << '(' << prod.price << ',' << prod.weight << ')' << endl;
    for (long long i = 2; i < stats.cycle_end; ++i) {
      prod.nextProduct(M, K, A, B, C, D);
      bool foundBetterThanMe = false, foundWorseThanMe = false;
      for (Products::iterator it = products.begin(); it != products.end();) {
        bool bImBetter = prod.isBetterThan(*it);
        bool bImWorse = it->isBetterThan(prod);
        if (!bImBetter && !bImWorse) {
          ++it;
          continue;
        }
        else {
          if (bImBetter) {
            foundWorseThanMe = true;
            if (it->isBargain) {
              it->isBargain = false;
              stats.updateStats(it->idx, -1, BARGAIN);
              //cout << '(' << it->price << ',' << it->weight << ") not a bargain" << endl;
            }
          }
          if (bImWorse) {
            foundBetterThanMe = true;
            if (it->isTerrible) {
              it->isTerrible = false;
              stats.updateStats(it->idx, -1, TERRIBLE);
              //cout << '(' << it->price << ',' << it->weight << ") not a terrible" << endl;
            }
          }
          if (!it->isBargain && !it->isTerrible)
            it = products.erase(it);
          else
            ++it;
        }
      }
      /*
      cout << '(' << prod.price << ',' << prod.weight << ')'
           << ", isBargin:" << (foundBetterThanMe?'N':'Y')
           << ", isTerrible:" << (foundWorseThanMe? 'N':'Y')
           << endl;
      */
      if (foundWorseThanMe && foundBetterThanMe)
        continue;
      prod.isTerrible = (!foundWorseThanMe);
      if (prod.isTerrible) {
        stats.updateStats(prod.idx, 1, TERRIBLE);
      }
      prod.isBargain = (!foundBetterThanMe);
      if (prod.isBargain) {
        stats.updateStats(prod.idx, 1, BARGAIN);
      }
      products.push_front(prod);
    }

    long long bargain_count = stats.getCount(BARGAIN);
    long long terrible_count = stats.getCount(TERRIBLE);
    /*
    cout << "Brute force search...";
    int brute_b, brute_t;
    bruteForce(N, P1, W1, M, K, A, B, C, D, brute_b, brute_t);
    cout << "...done" << endl;
    if (brute_b != bargain_count)
      cout << "Case #" << test_idx+1 << " bargain incorrect: " << brute_b << ' ' << bargain_count << endl;
    if (brute_t != terrible_count)
      cout << "Case #" << test_idx+1 << " terrible incorrect: " << brute_t << ' ' << terrible_count << endl;
    */
    cout << "Case #" << test_idx+1 << ": " << terrible_count << ' ' << bargain_count << endl;
  }

  return 0;
}



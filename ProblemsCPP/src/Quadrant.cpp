#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <ctime>
#include <ctype.h>

using namespace std;

#define NEXT_LINE(p) {while (*(p) != '\n') ++(p); ++(p);}
#define SKIP_SPACE(p) {while (*(p) != '\n' && isspace(*(p))) ++(p);}
#define SKIP_NON_SPACE(p) {while (*(p) != '\n' && !isspace(*(p))) ++(p);}

template<class T, int SIZE>
class NBitNum {
public:
  NBitNum()
  {
    array_size = ceil(SIZE/UNIT_SIZE);
    value = new T[array_size];
    for (int i = 0; i < array_size; ++i)
      value[i] = 0;
  }

  ~NBitNum()
  {
    delete [] value;
  }

  // bit is from left to right
  void set(int bit, unsigned val)
  {
    int idx = bit / UNIT_SIZE;
    int bit_idx = bit % UNIT_SIZE;
    bit_idx = UNIT_SIZE - 1 - bit_idx;
    T b = (1 << bit_idx);
    if (val) {
      value[idx] |= b;
    }
    else {
      value[idx] &= (~b);
    }
  }

  // bit is from left to right
  unsigned getBit(int bit) const
  {
    int idx, bit_idx;
    idx = bit / UNIT_SIZE;
    bit_idx = bit % UNIT_SIZE;
    bit_idx = UNIT_SIZE - 1 - bit_idx;
    T b = (1 << bit_idx);
    return (value[idx] & b ? 1 : 0);
  }

//private:
  static const int UNIT_SIZE = sizeof(T)*8; // in bits

  int array_size;
  T* value; // least sig. to most sig.
};

const static int MAX_N = 100000;
static int all_points[MAX_N];
typedef NBitNum<unsigned char, MAX_N> BitSet;
static BitSet quadrantBits[4];

enum {
  REFLECT_X = 0,
  REFLECT_Y = 1
};

enum {
  QUADRANT_1 = 0,
  QUADRANT_2 = 1,
  QUADRANT_3 = 2,
  QUADRANT_4 = 3,
};

static int reflect_matrix[4][2];
static unsigned char bitsCountTable[256];
static void initValues()
{
  reflect_matrix[QUADRANT_1][REFLECT_X] = QUADRANT_4;
  reflect_matrix[QUADRANT_1][REFLECT_Y] = QUADRANT_2;
  reflect_matrix[QUADRANT_2][REFLECT_X] = QUADRANT_3;
  reflect_matrix[QUADRANT_2][REFLECT_Y] = QUADRANT_1;
  reflect_matrix[QUADRANT_3][REFLECT_X] = QUADRANT_2;
  reflect_matrix[QUADRANT_3][REFLECT_Y] = QUADRANT_4;
  reflect_matrix[QUADRANT_4][REFLECT_X] = QUADRANT_1;
  reflect_matrix[QUADRANT_4][REFLECT_Y] = QUADRANT_3;

  for (unsigned i = 0; i < 256; ++i) {
    unsigned char bitCount = 0;
    for (int bit = 0; bit < 8; ++bit) {
      if (i & (1 << bit))
        ++bitCount;
    }
    bitsCountTable[i] = bitCount;
    //cout << i << ':' << (unsigned)bitCount << endl;
  }
}

static int getQuadrant(int x, int y)
{
  if (x > 0)
    return (y > 0 ? QUADRANT_1 : QUADRANT_4);
  return (y > 0 ? QUADRANT_2 : QUADRANT_3);
}

static void reflectPoints(int start, int end, int axis)
{
  for (int i = start; i <= end; ++i) {
    int old_quad = all_points[i];
    int new_quad = reflect_matrix[old_quad][axis];
    all_points[i] = new_quad;
    //cout << "Reflecting " << i+1 << " from " << old_quad+1 << " to " << new_quad+1 << endl;
    quadrantBits[old_quad].set(i, 0);
    quadrantBits[new_quad].set(i, 1);
  }

}

static void countBetween(unsigned start, unsigned end)
{
  unsigned idx_start = start / 8;
  unsigned shift_start = start % 8;
  unsigned mask_start = ~(255 >> shift_start); // 1100000 if 2
  unsigned idx_end = end / 8;
  unsigned shift_end = end % 8 + 1;
  unsigned mask_end = (255 >> shift_end); // 00000011 if 5+1
  for (int i = QUADRANT_1; i <= QUADRANT_4; ++i) {
    int count = 0;
    const BitSet & bs = quadrantBits[i];
    for (size_t bit = idx_start; bit <= idx_end; ++bit)
      count += bitsCountTable[bs.value[bit]];
    // Remove partial start & end
    count -= bitsCountTable[bs.value[idx_start] & mask_start];
    count -= bitsCountTable[bs.value[idx_end] & mask_end];
    cout << count;
    if (i == QUADRANT_4)
      cout << endl;
    else
      cout << ' ';
  }
}

static int runTest()
{
  BitSet & bs = quadrantBits[0];
  bs.set(1, 1);
  bs.set(2, 1);
  bs.set(3, 1);
  bs.set(2, 0);
  bs.set(4, 1);

  bs.set(8, 1);
  bs.set(15, 1);
  bs.set(13, 1);
  bs.set(14, 1);
  bs.set(13, 0);

  bs.set(23, 1);
  bs.set(16, 1);
  bs.set(17, 1);
  cout << "Value: " << (unsigned)bs.value[0] << ' ' << (unsigned)bs.value[1] << ' ' << (unsigned)bs.value[2] << endl;
  countBetween(4, 21);

  return 0;
}

static int generateTestFile()
{
  int MAX_Q = 1000000;
  cout << MAX_N << endl;
  srand(time(NULL));
  for (int i = 0; i < MAX_N; ++i) {
    int x = rand() % 2 ? INT_MAX : -INT_MAX;
    int y = rand() % 2 ? INT_MAX : -INT_MAX;
    cout << x << ' ' << y << endl;
  }
  cout << MAX_Q << endl;
  for (int i = 0; i < MAX_Q; ++i) {
    int op = rand() % 3;
    int point = rand() * 4 + rand() % 4;
    if (point >= MAX_N)
      point = MAX_N - 1;
    int point2 = rand() * 4 + rand() % 4;
    if (point2 >= MAX_N)
      point2 = MAX_N - 1;
    if (point > point2) {
      int tmp = point2;
      point2 = point;
      point = tmp;
    }
    char op_char = (op == 0 ? 'C' : (op == 1 ? 'X' : 'Y'));
    cout << op_char << ' ' << point << ' ' << point2 << endl;
  }
  return 0;
}

int quadrantMain(void)
{
  initValues();

  //return generateTestFile();
  //return runTest();

  int N;
  cin >> N;

  int buf_size = 20*1024*1024;
  char *my_buffer = new char[buf_size];
  if (!my_buffer) {
    cerr << "Unable to allocate buffer!" << endl;
    return -1;
  }
  memset(my_buffer, '\n', buf_size);
  cin.read(my_buffer, buf_size);
  char *p = my_buffer;
  int point = 0;
  NEXT_LINE(p);
  while (point < N) {
    SKIP_SPACE(p);
    int x = atoi(p);
    SKIP_NON_SPACE(p);
    int y = atoi(p);
    //cout << "x=" << x << ", y=" << y << endl;
    int quad = getQuadrant(x, y);
    all_points[point] = quad;
    quadrantBits[quad].set(point, 1);
    NEXT_LINE(p);
    ++point;
  }
  int Q = atoi(p);
  NEXT_LINE(p);
  int query = 0;
  while (query < Q) {
    SKIP_SPACE(p);
    char op = *p;
    ++p;
    SKIP_SPACE(p);
    int start_idx = atoi(p) - 1;
    SKIP_NON_SPACE(p);
    int end_idx = atoi(p) - 1;
    switch(op) {
    case 'X':
      reflectPoints(start_idx, end_idx, REFLECT_X);
      /*
      cout << (unsigned)quadrantBits[0].value[0] << ' '
           << (unsigned)quadrantBits[1].value[0] << ' '
           << (unsigned)quadrantBits[2].value[0] << ' '
           << (unsigned)quadrantBits[3].value[0] << endl;
      */
      ++query;
      break;
    case 'Y':
      reflectPoints(start_idx, end_idx, REFLECT_Y);
      /*
      cout << (unsigned)quadrantBits[0].value[0] << ' '
           << (unsigned)quadrantBits[1].value[0] << ' '
           << (unsigned)quadrantBits[2].value[0] << ' '
           << (unsigned)quadrantBits[3].value[0] << endl;
      */
      ++query;
      break;
    case 'C':
      countBetween(start_idx, end_idx);
      /*
      cout << (unsigned)quadrantBits[0].value[0] << ' '
           << (unsigned)quadrantBits[1].value[0] << ' '
           << (unsigned)quadrantBits[2].value[0] << ' '
           << (unsigned)quadrantBits[3].value[0] << endl;
      */
      ++query;
      break;
    default:
      cerr << "Unknown op: '" << op << "'" << endl;
      break;
    }
    NEXT_LINE(p);
  }

  delete [] my_buffer;
  return 0;
}



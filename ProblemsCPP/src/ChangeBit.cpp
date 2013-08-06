#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <limits>

using namespace std;

#define NEXT_LINE(p) {while (*(p) != '\n') ++(p); ++(p);}
#define SKIP_SPACE(p) {while (*(p) != '\n' && isspace(*(p))) ++(p);}
#define SKIP_NON_SPACE(p) {while (*(p) != '\n' && !isspace(*(p))) ++(p);}

typedef enum {
  QUERY_SET_A = 1,
  QUERY_SET_B = 2,
  QUERY_GET_C = 3,
} QueryEnum;

template<class T>
class NBitNum {
public:
  NBitNum(const string& str, int size)
  {
    array_size = size/UNIT_SIZE+2; // +1 for C=A+B, another +1 for rounding
    value = new T[array_size];
    for (int i = 0; i < array_size; ++i)
      value[i] = 0;
    int str_end = str.length() - 1;
    int idx, bit_idx;
    for (int i = str_end; i >= 0; --i)
      setBit(str_end - i, str[i]-'0', idx, bit_idx);
  }

  ~NBitNum()
  {
    delete [] value;
  }

  int setBit(int bit, unsigned val, int &idx, int &bit_idx)
  {
    idx = bit / UNIT_SIZE;
    bit_idx = bit % UNIT_SIZE;
    T b = (1 << bit_idx);
    unsigned old_val = (value[idx] & b ? 1 : 0);
    if (old_val == val)
      return 0;
    if (val) {
      value[idx] |= b;
    }
    else {
      value[idx] &= (~b);
    }

    return (val - old_val);
  }

  unsigned getBit(int bit)
  {
    int idx, bit_idx;
    idx = bit / UNIT_SIZE;
    bit_idx = bit % UNIT_SIZE;
    T b = (1 << bit_idx);
    return (value[idx] & b ? 1 : 0);
  }

  void addAtBit(int idx, int bit_idx)
  {
    T add_val = 1 << bit_idx;
    while (add_val > 0 && idx < array_size) {
      if (value[idx] > numeric_limits<T>::max() - add_val) {
        value[idx] += add_val;
        add_val = 1; // carry
        ++idx;
      }
      else {
        value[idx] += add_val;
        add_val = 0;
      }
    }
  }

  void subAtBit(int idx, int bit_idx)
  {
    T sub_val = 1 << bit_idx;
    while (sub_val > 0 && idx < array_size) {
      if (value[idx] < sub_val) {
        value[idx] -= sub_val;
        sub_val = 1; // borrow
        ++idx;
      }
      else {
        value[idx] -= sub_val;
        sub_val = 0;
      }
    }
  }

  // Assume same size;
  void add(const NBitNum &num1, const NBitNum &num2)
  {
    int carry = 0;
    for (int i = 0; i < num1.array_size; ++i) {
      // Handle a special underflow case
      if (num2.value[i] == numeric_limits<T>::max() && carry == 1) {
        value[i] = num1.value[i];
        continue;
      }
      int saved_carry = carry;
      // Now numeric_limits<T>::max() - num2.value[i] - carry will not underflow
      if (num1.value[i] > numeric_limits<T>::max() - num2.value[i] - carry)
        carry = 1;
      else
        carry = 0;
      value[i] = num1.value[i] + num2.value[i] + saved_carry;
    }
  }

  void printNums()
  {
    for (int i = array_size - 1; i >= 0; --i)
    {
      cout << (unsigned long long)value[i] << ' ';
    }
    cout << endl;
  }

private:
  static const int UNIT_SIZE = sizeof(T)*8; // in bits

  int array_size;
  T* value; // least sig. to most sig.
};

typedef NBitNum<unsigned> NBitType;

int changeBitMain(void)
{
  bool bImmediateUpdate = true;
  //int time_begin = time(NULL);
  int buf_size = 20*1024*1024;
  char *my_buffer = new char[buf_size];
  if (!my_buffer) {
    cerr << "Unable to allocate buffer!" << endl;
    return -1;
  }
  memset(my_buffer, '\n', buf_size);
  int N, Q;
  string a_str, b_str;
  string buf;
  getline(cin, buf);
  istringstream iss_N_Q(buf);
  iss_N_Q >> N >> Q;
  getline(cin, a_str);
  getline(cin, b_str);
  NBitType num_A(a_str, N), num_B(b_str, N), num_C("", N);
  if (bImmediateUpdate)
    num_C.add(num_A, num_B);
  cin.read(my_buffer, buf_size);
  char *p = my_buffer;
  int query_read = 0;
  while (query_read < Q) {
    SKIP_SPACE(p);
    int q;
    if (*p == 's') {
      q = (*(p+4)== 'a' ? QUERY_SET_A : QUERY_SET_B);
    }
    else if (*p == 'g')
      q = QUERY_GET_C;
    else {
      //cerr << "Unknown command: '" << line_str << "'!" << endl;
      NEXT_LINE(p);
      continue;
    }
    p += 5;
    SKIP_SPACE(p);
    int idx = atoi(p);
    int val = 0;
    if (q == QUERY_SET_B || q == QUERY_SET_A) {
      SKIP_NON_SPACE(p);
      val = (atoi(p) ? 1 : 0);
    }
    switch (q) {
    case QUERY_SET_A:
    case QUERY_SET_B:
    {
      NBitType &num = (q == QUERY_SET_A ? num_A : num_B);
      int unit_idx, bit_idx;
      int cmp = num.setBit(idx, val, unit_idx, bit_idx);
      if (bImmediateUpdate) {
        if (cmp > 0)
          num_C.addAtBit(unit_idx, bit_idx);
        else if (cmp < 0)
          num_C.subAtBit(unit_idx, bit_idx);
      }
      break;
    }
    case QUERY_GET_C:
      if (!bImmediateUpdate)
        num_C.add(num_A, num_B);
      cout << num_C.getBit(idx);
      break;
    }
    ++query_read;
    NEXT_LINE(p);
  }
  cout << endl;
  //cerr << "Total time:" << time(NULL)-time_begin << endl;
  delete [] my_buffer;
  return 0;
}

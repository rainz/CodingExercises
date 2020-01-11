#include <iostream>
#include <cassert>

using namespace std;

template <class T>
class CircularBuffer {
public:
  CircularBuffer(size_t capacity) : _capacity(capacity), start_idx(0), end_idx(0), is_empty(true)
  {
    _data = new T[_capacity];
  }
  
  ~CircularBuffer() { delete [] _data; }

  bool push_back(const T &val) {
    if (size() >= _capacity)
      return false;
    is_empty = false;
    _data[end_idx] = val;
    end_idx = (end_idx + 1) % _capacity;
    return true;
  }
  
  T pop_front() {
    if (size() == 0) {
      throw runtime_error("Buffer empty error");
    }
    if (size() == 1)
      is_empty = true;
    size_t ret_idx = start_idx;
    start_idx = (start_idx + 1) % _capacity;
    return _data[ret_idx];
  }
  
  size_t size() {
    size_t sz = (end_idx + _capacity - start_idx) % _capacity;
    if (sz == 0 && !is_empty)
      sz = _capacity;
    return sz;
  }

private:
  size_t _capacity;
  size_t start_idx;
  size_t end_idx;
  bool is_empty;
  
  T *_data;
};

int main() {
  size_t testCap = 3;
  CircularBuffer<size_t> cb(testCap);
  
  // Basic tests
  assert(cb.size() == 0);
  for (size_t i = 0; i < testCap; ++i) {
    assert(cb.push_back(i));
    assert(cb.size() == i+1);
  }
  assert(!cb.push_back(0));
  assert(cb.size() == testCap);
  
  for (size_t i = 0; i < testCap; ++i) {
    size_t val = cb.pop_front();
    assert(val == i);
    assert(cb.size() == testCap - i - 1);
  }
  
  // Wrap around cases
  for (size_t i = 0; i < testCap; ++i) {
    cb.push_back(i);
  }
  for (size_t i = 0; i < testCap; ++i) {
    cb.pop_front();
    assert(cb.push_back(0));
    assert(cb.size() == testCap);
  }
    
  return 0;
}

#include <vector>

using namespace std;

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
 };

class Intervals {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> answer;
        int newStart = newInterval.start;
        int newEnd = newInterval.end;
        int idx = 0, count = intervals.size();
        if (count == 0) {
          // special case 1
          answer.push_back(newInterval);
          return answer;
        }
        while (idx < count) {
          const Interval &intv = intervals[idx];
          int oldStart = intv.start;
          int oldEnd = intv.end;
          if (newStart > oldEnd) {
            answer.push_back(intv);
            ++idx;
            if (idx >= count) {
              // Special case 2
              answer.push_back(newInterval);
            }
            continue;
          }
          if (newEnd < oldStart) {
            answer.push_back(newInterval);
            break;
          }
          int outStart = min(newStart, oldStart);
          while (idx < count && intervals[idx].end <= newEnd)
            ++idx;
          if (idx < count && intervals[idx].start <= newEnd)
            ++idx;
          int outEnd = max(newEnd, intervals[idx-1].end);
          Interval outInterval(outStart, outEnd);
          answer.push_back(outInterval);
          break;
        }
        //Copy the rest
        for (;idx < count; ++idx)
          answer.push_back(intervals[idx]);
        return answer;
    }
};

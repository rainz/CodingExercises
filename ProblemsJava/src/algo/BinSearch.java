package algo;

public class BinSearch {

  /*Given a sorted array and a target value, return the index if the target is found. 
   * If not, return the index where it would be if it were inserted in order.
   * You may assume no duplicates in the array.
   */
  public int searchInsert(int[] A, int target) {
      if (A.length == 0) return 0;
      int lower = 0, upper = A.length - 1;
      
      if (target <= A[lower]) return lower;
      if (target == A[upper]) return upper;
      if (target > A[upper]) return upper+1;
      
      while (lower < upper - 1) {
          int mid = (lower + upper) / 2;
          if (A[mid] == target) return mid;
          if (A[mid] < target) {
              lower = mid;
              continue;
          }
          upper = mid;
      }
      
      if (target > A[lower]) return upper;
      return lower;
  }
  
  /* Given a sorted array of integers, find the starting and ending position of a given target value.
   * Your algorithm's runtime complexity must be in the order of O(log n).
   * If the target is not found in the array, return [-1, -1].
   */
  public int[] searchRange(int[] A, int target) {
      int[] answer = new int[2];
      answer[0] = answer[1] = -1;
      int rightStart = 0;
      
      // Find left boundary
      int lower = 0, upper = A.length-1;
      while (lower <= upper) {
          int mid = (lower + upper) / 2;
          int midVal = A[mid];
          if (midVal == target) {
              if (mid > rightStart) rightStart = mid;
              if (mid == 0) {
                  answer[0] = mid; // found left boundary which is start of input
                  break;
              }
              upper = mid - 1;
          }
          else if (midVal < target) {
              if (mid == A.length - 1) break; // no solution
              if (A[mid+1] == target) {
                  answer[0] = mid+1; // found left boundary.
                  break;
              }
              lower = mid + 1;
          }
          else upper = mid - 1;
      }
      if (answer[0] < 0) return answer;
      
      // Find right boundary
      lower = Math.max(rightStart, answer[0]);
      upper = A.length - 1;
      while (lower <= upper) {
          int mid = (lower + upper) / 2;
          int midVal = A[mid];
          if (midVal == target) {
              if (mid == A.length - 1)  {
                  answer[1] = mid; // found right boundary which is end of input
                  break;
              }
              lower = mid + 1;
          }
          else {
              // midVal > target, mid must be > 0
              if (A[mid-1] == target) {
                  answer[1] = mid-1; // found right boundary
                  break;
              }
              upper = mid - 1;
          }
      }
      
      return answer;
  }
}

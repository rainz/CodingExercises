package algo;

import java.util.ArrayList;

public class PascalTriangle {
  
  /* Given numRows, generate the first numRows of Pascal's triangle. */
  public ArrayList<ArrayList<Integer>> generate(int numRows) {
    ArrayList<ArrayList<Integer>> answer = new ArrayList<ArrayList<Integer>>();
    if (numRows <= 0) return answer;
    
    ArrayList<Integer> prev = new ArrayList<Integer>();
    prev.add(1);
    answer.add(prev);
    for (int row = 2; row <= numRows; ++row) {
        ArrayList<Integer> curr = new ArrayList<Integer>();
        for (int i = 0; i < row; ++i) {
            int val1 = (i <= 0 ? 0 : prev.get(i-1));
            int val2 = (i >= row-1 ? 0 : prev.get(i));
            curr.add(val1+val2);
        }
        answer.add(curr);
        prev = curr;
    }
    
    return answer;
  }

  /* Given an index k, return the kth row of the Pascal's triangle. k is 0-based. */
  public ArrayList<Integer> getRow(int rowIndex) {
      ArrayList<Integer> prev = new ArrayList<Integer>();
      if (rowIndex < 0) return prev;
      
      ArrayList<Integer> curr = new ArrayList<Integer>();
      for (int i = 0; i <= rowIndex; ++i) {
          prev.add(0);
          curr.add(0);
      }
      prev.set(0, 1);
      
      for (int row = 1; row <= rowIndex; ++row) {
          for (int i = 0; i <= row; ++i) {
              int val1 = (i <= 0 ? 0 : prev.get(i-1));
              int val2 = (i >= row ? 0 : prev.get(i));
              curr.set(i, val1+val2);
          }
          ArrayList<Integer> tmp = prev;
          prev = curr;
          curr = tmp;
      }
      
      return prev;
          
  }
  

}

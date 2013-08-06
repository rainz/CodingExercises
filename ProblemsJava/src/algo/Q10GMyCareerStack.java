package algo;

import java.util.ArrayList;
import java.util.HashMap;

public class Q10GMyCareerStack {
  //You have an array of 0s and 1s and you want to output all the intervals (i, j) where the number of 0s and numbers of 1s are equal.
  //Example:
  //positions = 0 1 2 3 4 5 6 7 8
  //Array =     0 1 0 0 1 1 1 1 0
  //One interval is (0, 1) because there the number of 0 and 1 are equal. There are many other intervals, find all in minimum time possible.
  
  //Solution:
  //For each element, compute the difference of # 1s and # 0s before this element.
  //Then each equal pair consists of such a range.
  //Note the boundary condition in this program!!!
  
  public boolean runTest()
  {
    int testArray[] = {0, 1, 0, 0, 1, 1, 1, 1, 0};
    solution(testArray);
    return true;
  }
  
  private void solution(int [] numbers)
  {
    int count_0 = 0, count_1 = 0;
    HashMap<Integer, ArrayList<Integer>> equalIndices = new HashMap<Integer, ArrayList<Integer>>();
    
    // Handle boundary condition
    ArrayList<Integer> indices = new ArrayList<Integer>();
    indices.add(new Integer(-1));
    equalIndices.put(new Integer(0), indices);
    
    for (int i = 0; i < numbers.length; ++i)
    {
      if (numbers[i] != 0)
        ++count_1;
      else
        ++count_0;
      
      Integer idx = new Integer(i);
      Integer diff = new Integer(count_1 - count_0);
      if (equalIndices.containsKey(diff))
        indices = equalIndices.get(diff);
      else {
        indices = new ArrayList<Integer>();
        equalIndices.put(diff, indices);
      }
      indices.add(idx);
      
    }
    int pair_count = 0;
    for (Integer val: equalIndices.keySet()) {
      ArrayList<Integer> arr = equalIndices.get(val);
      int len = arr.size();
      for (int i = 0; i < len; ++i)
        for (int j = i + 1; j < len; ++j) {
          System.out.println("" + (arr.get(i)+1) + ", " + arr.get(j));
          ++pair_count;
        }
    }
    System.out.println("Pair count: "+pair_count);
    
  }
}

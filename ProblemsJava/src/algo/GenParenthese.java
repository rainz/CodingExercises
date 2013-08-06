package algo;

import java.util.ArrayList;

public class GenParenthese {
  public void helper(ArrayList<String> answer, char [] solution, int len, int leftCount, int rightCount) {
    if (len == solution.length) {
        String paren = new String(solution);
        answer.add(paren);
        return;
    }
    if (leftCount > 0) {
        solution[len] = '(';
        helper(answer, solution, len+1, leftCount-1, rightCount);
    }
    if (leftCount < rightCount && rightCount > 0) {
        solution[len] = ')';
        helper(answer, solution, len+1, leftCount, rightCount-1);            
    }
  }

  public ArrayList<String> generateParenthesis(int n) {
    ArrayList<String> answer = new ArrayList<String>();    
    char [] solution = new char[n*2];    
    helper(answer, solution, 0, n, n);    
    return answer;
  }

}

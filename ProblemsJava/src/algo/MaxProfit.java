package algo;

public class MaxProfit {
  
  /* Say you have an array for which the ith element is the price of a given stock on day i.
   * If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), 
   * design an algorithm to find the maximum profit.
   */
  public int maxProfit1(int[] prices)
  {
    int maxProf = 0;
    int lowest = Integer.MAX_VALUE;

    for (int p : prices)
    {
      int profit = p - lowest;
      if (profit > maxProf)
        maxProf = profit;
      if (lowest > p)
        lowest = p;
    }

    return maxProf;
  }
  
  /*Say you have an array for which the ith element is the price of a given stock on day i.
   * Design an algorithm to find the maximum profit. 
   * You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time
   * (ie, you must sell the stock before you buy again).
   */
  public int maxProfit2(int[] prices) {
      int maxProf = 0;
      int prev = Integer.MAX_VALUE;
      for (int p: prices) {
          if (p > prev) maxProf += p - prev;
          prev = p;
      }
      return maxProf;
  }

  /* Say you have an array for which the ith element is the price of a given stock on day i.
   * Design an algorithm to find the maximum profit. You may complete at most two transactions.
   * Note:
   * You may not engage in multiple transactions at the same time
   * (ie, you must sell the stock before you buy again).
   */
  public int maxProfit(int[] prices) {
      int [] transaction1 = new int[prices.length];
      int [] transaction2 = new int[prices.length];
      
      int low = Integer.MAX_VALUE, hi = Integer.MIN_VALUE;
      int maxProf1 = 0, maxProf2 = 0;
      for (int i = 0; i < prices.length; ++i) {
          // Compute max profit from the left.
          int p = prices[i];
          if (p < low) low = p;
          int prof = p - low;
          if (prof > maxProf1) maxProf1 = prof;
          transaction1[i] = maxProf1;
          
          // Compute max profit from the right.
          int rightIdx = prices.length - 1- i;
          p = prices[rightIdx];
          if (p > hi) hi = p;
          prof = hi - p;
          if (prof > maxProf2) maxProf2 = prof;
          transaction2[rightIdx] = maxProf2;            
      }
      
      int maxProf = 0;
      for (int mid = 0; mid < prices.length; ++mid) {
          int profit = transaction1[mid];
          profit += (mid+1 < prices.length ? transaction2[mid+1] : 0);
          if (profit > maxProf) maxProf = profit;
      }
      
      return maxProf;        
  }
}

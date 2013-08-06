package algo;

import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Comparator;

import algo.ListNode;


public class MergeKLists {
  public ListNode mergeKLists(ArrayList<ListNode> lists) {
    ListNode answer = null;
    if (lists == null || lists.isEmpty()) return answer;
    
    PriorityQueue<ListNode> pq = 
      new PriorityQueue<ListNode>(11, 
                                  new Comparator<ListNode>() {
                                      @Override
                                      public int compare(ListNode a, ListNode b) {
                                          return (a.val > b.val ? 1 : (a.val < b.val ? -1 : 0));
                                      }
                                  });
    for (int i = 0; i < lists.size(); ++i) {
        ListNode l = lists.get(i);
        if (l != null) {
            pq.add(l);
        }
            
    }
    ListNode tail = null;
    while (!pq.isEmpty()) {
        ListNode n = pq.remove();
        if (n.next != null)
            pq.add(n.next);
        if (answer == null) {
            answer = n;
            tail = answer;
        }
        else {
            tail.next = n;
            tail = tail.next;
        }
        tail.next = null;
    }
    return answer;
}

}

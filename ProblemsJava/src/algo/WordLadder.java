package algo;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class WordLadder {
    // Word Ladder 1
    public int ladderLength(String start, String end, HashSet<String> dict) {
        if (start.equals(end)) return 1;
        int answer = 2;
        Queue<String> currQ = new LinkedList<String>();
        Queue<String> nextQ = new LinkedList<String>();
        HashSet<String> checked = new HashSet<String>();
        currQ.add(start);
        checked.add(start);
        
        while (!currQ.isEmpty()) {
            char [] chars = currQ.remove().toCharArray();
            for (int i = 0; i < chars.length; ++i) {
                char orig = chars[i];
                for (char c = 'a'; c <= 'z'; ++c) {
                    chars[i] = c;
                    String s = new String(chars);
                    if (checked.contains(s)) continue;
                    if (s.equals(end)) return answer;
                    if (dict.contains(s)) {
                        nextQ.add(s);
                        checked.add(s);
                    }
                }
                chars[i] = orig;
            }
            if (currQ.isEmpty()) {
                currQ = nextQ;
                nextQ = new LinkedList<String>();
                ++answer;
            }            
        } 
        
        return 0;
    }
    
    // Word Ladder 2
    // Times out on large tests!!!
    private static class WordNode {
        public String word;
        public WordNode previous;
        public WordNode(String w, WordNode p) {
            word = w;
            previous = p;
        }
    }
    private ArrayList<String> buildSolution(WordNode node, int steps) {
        ArrayList<String> sol = new ArrayList<String>(steps);
        while (node != null) {
            sol.add(node.word);
            node = node.previous;
        }
        Collections.reverse(sol);
        return sol;
    }
    public ArrayList<ArrayList<String>> findLadders(String start, String end, HashSet<String> dict) {
        ArrayList<ArrayList<String>> answer = new ArrayList<ArrayList<String>>();
        if (start.equals(end)) {
            ArrayList<String> solution = new ArrayList<String>();
            solution.add(start);
            solution.add(end);
            answer.add(solution);
            return answer;
        }
        Queue<WordNode> currQ = new LinkedList<WordNode>();
        Queue<WordNode> nextQ = new LinkedList<WordNode>();
        HashSet<String> checked = new HashSet<String>();
        checked.add(start);
        int steps = 2;
        currQ.add(new WordNode(start, null));
        
        while (!currQ.isEmpty()) {
            WordNode node = currQ.remove();
            char [] chars = node.word.toCharArray();
            for (int i = 0; i < chars.length; ++i) {
                char orig = chars[i];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == orig) continue;
                    chars[i] = c;
                    String s = new String(chars);
                    if (dict.contains(s) && !checked.contains(s)) {
                        if (s.equals(end)) {
                            WordNode newNode = new WordNode(s, node);
                            ArrayList<String> solution = buildSolution(newNode, steps);
                            answer.add(solution);
                            continue;
                        }
                        nextQ.add(new WordNode(s, node));
                    }
                }
                chars[i] = orig;
            }
            if (currQ.isEmpty()) {
                if (!answer.isEmpty()) break;
                // Only add to 'checked' when entire level is done,
                // because it's okay to have dups on the same level.
                for (WordNode wn: nextQ) checked.add(wn.word);
                currQ = nextQ;
                nextQ = new LinkedList<WordNode>();
                ++steps;
            }            
        }
        
        return answer;
    }
}

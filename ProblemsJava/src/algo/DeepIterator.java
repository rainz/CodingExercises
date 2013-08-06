package algo;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Stack;
import java.util.Collection;

public class DeepIterator {
	Stack<Iterator<Object>> stk = new Stack<Iterator<Object>>();
	
	public DeepIterator(Collection<Object> c) {
		if (c != null) {
			stk.push(c.iterator());
		}
	}

	public Object next() {
		while (!stk.isEmpty()) {
			for (Iterator<Object> it = stk.peek(); it.hasNext();) {
				Object obj = it.next();
				if (!(obj instanceof Collection)) {
					return obj;
				}
				@SuppressWarnings("unchecked")
				Collection<Object> c = (Collection<Object>)obj;
				it = c.iterator();
				stk.push(it);
			}
			stk.pop();
		}
		return null;
	}
	
	protected static Collection<Object> buildTestCase(String s) {
		if (s.length() < 2 || s.charAt(0) != '{') {
			return null;
		}
		
		Stack<Collection<Object>> stk = new Stack<Collection<Object>>();
		System.out.println("Adding ArrayList");
		Collection<Object> collection = new ArrayList<Object>();
		stk.push(collection);
		int currNum = 0;
		boolean hasNumber = false;
		for (int i = 1; i < s.length(); ++i) {
			char c = s.charAt(i);
			if (Character.isDigit(c)) {
				currNum = currNum*10 + c - '0';
				hasNumber = true;
			}
			else {
				if (hasNumber) {
					collection.add(new Integer(currNum));
					System.out.println("Adding number "+currNum);
					currNum = 0;
					hasNumber = false;
				}
				if (c == '{') {
					Collection<Object> col = new ArrayList<Object>();
					System.out.println("Adding ArrayList");
					collection.add(col);
					stk.push(col);
					collection = col;
					continue;
				}
				if (c == '}') {
					System.out.println("Done with ArrayList, size="+collection.size());
					collection = stk.pop();
					continue;
				}
			}
		}
		if (!stk.isEmpty()) {
			System.err.println("Stack still has elements:"+stk.size());
		}
		return collection;
	}
	
	public static void test() {
		//Collection<Object> testCase = buildTestCase("{1, 2, {{{3, 4, 5}}}, {}, 6, {{}}, 7, 8}");
		//Collection<Object> testCase = buildTestCase("{{{2,3}}}");
		Collection<Object> testCase = buildTestCase("{{}, {}, {{}}, {11,{22}}}");
		DeepIterator deepIt = new DeepIterator(testCase);
		for (Object obj = deepIt.next(); obj != null; obj = deepIt.next()) {
			Integer intObj = (Integer)obj;
			System.out.print("" + intObj.intValue() + ", ");			
		}
		System.out.println();
	}
}

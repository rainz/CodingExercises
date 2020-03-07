#include <iostream>
#include <queue>

using namespace std;


class StreamProcessor {
public:
    StreamProcessor() : kth(10) {}

    StreamProcessor(int k) : kth(k) {}
    
    void addNum(double num) {
        // Add num to PQ for finding kth element
        kthPQ.push(num);
        while (kthPQ.size() > kth)
            kthPQ.pop();

        // Add num to median PQs
        if (maxPQ.empty() || maxPQ.top() > num)
            maxPQ.push(num);
        else
            minPQ.push(num);
        // Balance median PQs
        while (maxPQ.size() > minPQ.size()+1) {
            int val = maxPQ.top(); maxPQ.pop();
            minPQ.push(val);
        }
        while (maxPQ.size() < minPQ.size()) {
            int val = minPQ.top(); minPQ.pop();
            maxPQ.push(val);
        }        
    }
    
    bool getMedian(double &result) {
        int totalSize = maxPQ.size() + minPQ.size();
        if (totalSize == 0)
            return false;
        if (totalSize % 2 == 1)
            result = maxPQ.top();
        else
            result = ((double)maxPQ.top() + minPQ.top()) / 2.0;        
        return true;
    }

    bool getKth(double &result) {
        if (kthPQ.size() < kth)
            return false;
        result = kthPQ.top();
        return true;
    }

private:
    // Use a min priority queue and a max priority queue for computing median
    // Either maxPQ and minPQ have same # elements, or maxPQ have one more than minPQ.
    priority_queue<double> maxPQ;
    priority_queue<double, vector<double>, greater<double>> minPQ;

    // Priority queue for kth element
    int kth;
    priority_queue<double> kthPQ;
};


int main(void)
{
    double d;
    StreamProcessor p;
    while (true) {
        cin >> d;
        p.addNum(d);
        double median, kth;
        cout << "Median=";
        if (p.getMedian(median))
            cout << median;
        else
            cout << "NaN";
        cout << ", 10th=";
        if (p.getKth(kth))
            cout << kth;
        else
            cout << "NaN";
        cout << endl;
    }
    return 0;
}
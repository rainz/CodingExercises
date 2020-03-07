/*
 * Author: Yu Zhao
 * Vatic Labs coding assigment
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Trade {
public:
    int time;
    string symbol;
    char side;
    double price;
    int qty;
    Trade() {}
    Trade(int t, const string& sym, char s, double p, int q):
          time(t), symbol(sym), side(s), price(p), qty(q) {}
};


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Please specific an input file!" << endl;
        return -1;
    }
    ifstream infile;
    infile.open(argv[1]);
    if (!infile) {
        cerr << "Can't open " << argv[1] << endl;
        return -1;
    }
    
    cout << setprecision(2) << fixed
         << "OPEN_TIME,CLOSE_TIME,SYMBOL,QUANTITY,PNL,OPEN_SIDE,CLOSE_SIDE,OPEN_PRICE,CLOSE_PRICE"
         << endl;

    string line;
    double total_pnl = 0;
    unordered_map<string, list<Trade>> order_map;
    while (getline(infile, line)) {
        if (line.length() == 0 || !isdigit(line[0]))
            continue; // skip title line/empty lines
        replace(line.begin(), line.end(), ',', ' ');
        istringstream iss(line);
        Trade trd;
        iss >> trd.time >> trd.symbol >> trd.side >> trd.price >> trd.qty;
        auto &trades = order_map[trd.symbol];
        if (trades.empty() || trades.front().side == trd.side) {
            // trd is an opening trade
            trades.push_back(trd);
            continue;
        }
        // trd is a closing trade. Pair it with opening trade(s)
        while (!trades.empty() && trd.qty > 0) {
            auto &opening = trades.front();
            int qty = min(opening.qty, trd.qty);
            opening.qty -= qty;
            trd.qty -= qty;
            auto &buy = trd.side == 'B' ? trd : opening;
            auto &sell = trd.side == 'S' ? trd : opening;
            double pnl = qty * (sell.price - buy.price);
            total_pnl += pnl;
            
            cout << opening.time << ',' << trd.time << ',' 
                 << trd.symbol << ',' << qty << ',' << pnl << ','
                 << opening.side << ',' << trd.side << ','
                 << opening.price << ',' << trd.price << endl;
            
            if (opening.qty == 0)
                trades.pop_front();
        }
        if (trd.qty > 0)
            trades.push_back(trd);
    }
    infile.close();

    cout << total_pnl << endl;
    return 0;
}
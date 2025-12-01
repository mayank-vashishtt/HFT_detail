#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

// Bids: Highest price first (descending)
// Asks: Lowest price first (ascending)
map<double, int, greater<double>> bids;
map<double, int> asks;

void matchOrders() {
    while (!bids.empty() && !asks.empty()) {
        double topBid = bids.begin()->first;
        int bidVol = bids.begin()->second;
        double topAsk = asks.begin()->first;
        int askVol = asks.begin()->second;

        if (topBid >= topAsk) {
            int tradeVolume = min(bidVol, askVol);
            cout << "Trade! Price: " << topAsk 
                 << ", Volume: " << tradeVolume << endl;

            bids[topBid] -= tradeVolume;
            asks[topAsk] -= tradeVolume;

            if (bids[topBid] == 0) bids.erase(topBid);
            if (asks[topAsk] == 0) asks.erase(topAsk);
        } else {
            break;
        }
    }
}

int main() {
    // Add some example orders
    // Bids (buyers): willing to buy at price and volume
    bids[101.5] = 50;
    bids[100.0] = 30;

    // Asks (sellers): willing to sell at price and volume
    asks[100.0] = 40;
    asks[102.0] = 20;

    cout << "Order book before matching:\n";
    cout << "Bids:\n";
    for (auto &b : bids)
        cout << "  Price: " << b.first << ", Volume: " << b.second << endl;
    cout << "Asks:\n";
    for (auto &a : asks)
        cout << "  Price: " << a.first << ", Volume: " << a.second << endl;

    cout << "\nMatching orders...\n";
    matchOrders();

    cout << "\nOrder book after matching:\n";
    cout << "Bids:\n";
    for (auto &b : bids)
        cout << "  Price: " << b.first << ", Volume: " << b.second << endl;
    cout << "Asks:\n";
    for (auto &a : asks)
        cout << "  Price: " << a.first << ", Volume: " << a.second << endl;

    return 0;
}

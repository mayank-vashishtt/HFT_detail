#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

map<double, int, greater<double>> bids;
map<double, int> asks;

void addBid(double price, int volume) {
    bids[price] += volume;
}
void addAsk(double price, int volume) {
    asks[price] += volume;
}

void matchOrders() {
    while (!bids.empty() && !asks.empty()) {
        double topBid = bids.begin()->first;
        int bidVol = bids.begin()->second;
        double topAsk = asks.begin()->first;
        int askVol = asks.begin()->second;

        if (topBid >= topAsk) {
            int tradeVolume = min(bidVol, askVol);
            cout << "Trade! Price: " << topAsk << ", Volume: " << tradeVolume << endl;
            bids[topBid] -= tradeVolume;
            asks[topAsk] -= tradeVolume;

            // Remove price if all shares are matched (filled)
            if (bids[topBid] == 0) bids.erase(topBid);
            if (asks[topAsk] == 0) asks.erase(topAsk);
        } else {
            break; // No match possible
        }
    }
}

int main() {
    addBid(100.05, 200); // Wants to buy 200 shares at 100.05
    addAsk(100.04, 150); // Wants to sell 150 shares at 100.04

    cout << "Before matching:" << endl;
    cout << "Bid: " << bids.begin()->first << ", Qty: " << bids.begin()->second << endl;
    cout << "Ask: " << asks.begin()->first << ", Qty: " << asks.begin()->second << endl;

    matchOrders();

    cout << "After matching:" << endl;
    if (!bids.empty())
        cout << "Remaining Bid: " << bids.begin()->first << ", Qty: " << bids.begin()->second << endl;
    if (!asks.empty())
        cout << "Remaining Ask: " << asks.begin()->first << ", Qty: " << asks.begin()->second << endl;

    return 0;
}

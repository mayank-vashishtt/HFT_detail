#include <iostream>
#include <map>
using namespace std;

// Buy orders: price, volume (highest price first)
map<double, int, greater<double>> bids;

// Sell orders: price, volume (lowest price first)
map<double, int> asks;

// Function to add a buy order
void addBid(double price, int volume) {
    bids[price] += volume;
}

// Function to add a sell order
void addAsk(double price, int volume) {
    asks[price] += volume;
}

// The matching engine: match if best bid >= best ask
void matchOrders() {
    while (!bids.empty() && !asks.empty()) {
        double topBid = bids.begin()->first;
        int bidVol = bids.begin()->second;
        double topAsk = asks.begin()->first;
        int askVol = asks.begin()->second;

        if (topBid >= topAsk) {
            // Trade occurs at topAsk price (standard)
            int tradeVolume = min(bidVol, askVol);
            cout << "Trade! Price: " << topAsk << ", Volume: " << tradeVolume << endl;

            // Update volumes
            bids[topBid] -= tradeVolume;
            asks[topAsk] -= tradeVolume;

            // Remove zeros
            if (bids[topBid] == 0) bids.erase(topBid);
            if (asks[topAsk] == 0) asks.erase(topAsk);
        } else {
            // No more matches
            break;
        }
    }
}

int main() {
    // Add some orders
    addBid(100.05, 200); // Bid: buy at 100.05, qty 200
    addBid(100.02, 100); // Bid: buy at 100.02, qty 100
    addAsk(100.04, 150); // Ask: sell at 100.04, qty 150
    addAsk(100.06, 100); // Ask: sell at 100.06, qty 100

    cout << "Order book before matching:" << endl;
    cout << "Best bid: " << bids.begin()->first << endl;
    cout << "Best ask: " << asks.begin()->first << endl;

    // Match orders
    matchOrders();

    cout << "Order book after matching:" << endl;
    if (!bids.empty())
        cout << "Best bid: " << bids.begin()->first << endl;
    else
        cout << "No more bids." << endl;
    if (!asks.empty())
        cout << "Best ask: " << asks.begin()->first << endl;
    else
        cout << "No more asks." << endl;

    return 0;
}

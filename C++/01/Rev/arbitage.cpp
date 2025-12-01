#include <iostream>
#include <chrono>
using namespace std;

// Struct to store bid/ask data for NSE and BSE
struct MarketData {
    double bid_nse;
    double ask_nse;
    double bid_bse;
    double ask_bse;
    long timestamp;
};

// Arbitrage bot class
class ArbitrageBot {
public:
    double min_profit_threshold = 0.01; // Only trade for profit above 1 paisa

    // Checks both directions for arbitrage opportunity
    void processMarketData(const MarketData& md) {
        // NSE -> BSE
        if (md.bid_bse > md.ask_nse) {
            double profit = md.bid_bse - md.ask_nse;
            if (profit > min_profit_threshold) {
                cout << "Arbitrage (NSE->BSE): Buy NSE @ " << md.ask_nse 
                     << ", Sell BSE @ " << md.bid_bse 
                     << " | Profit: " << profit 
                     << " | Timestamp: " << md.timestamp << endl;
            }
        }

        // BSE -> NSE
        if (md.bid_nse > md.ask_bse) {
            double profit = md.bid_nse - md.ask_bse;
            if (profit > min_profit_threshold) {
                cout << "Arbitrage (BSE->NSE): Buy BSE @ " << md.ask_bse
                     << ", Sell NSE @ " << md.bid_nse
                     << " | Profit: " << profit 
                     << " | Timestamp: " << md.timestamp << endl;
            }
        }
    }
};

int main() {
    ArbitrageBot bot;
    // Example market data, in reality these would update every millisecond
    MarketData md = {100.04, 100.05, 100.08, 100.11, 
        chrono::system_clock::now().time_since_epoch().count()};
    bot.processMarketData(md);

    // Try with another set where BSE -> NSE is profitable
    MarketData md2 = {100.09, 100.13, 100.06, 100.08, 
        chrono::system_clock::now().time_since_epoch().count()};
    bot.processMarketData(md2);

    return 0;
}

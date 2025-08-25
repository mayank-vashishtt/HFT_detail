#include<iostream>
#include<math.h>
using namespace std;

struct Order{

    int id; 
    bool isBuy; // true for buy
    int qty;
    double price;
};

struct MatchResult {
    int qtyFilled;
};


MatchResult matchOrders(Order& a, Order& b) {
    int qtyFilled = 0;
    if (a.isBuy && !b.isBuy && a.price >= b.price) {
        qtyFilled = min(a.qty, b.qty);
        a.qty -= qtyFilled;
        b.qty -= qtyFilled;
    }
    else if (b.isBuy && !a.isBuy && b.price >= a.price) {
        qtyFilled = min(a.qty, b.qty);
        a.qty -= qtyFilled;
        b.qty -= qtyFilled;
    }
    MatchResult result;
    result.qtyFilled = qtyFilled;
    return result;
}





int main(){


    Order a = {1, true, 500, 10};
    Order b = {2, false, 500, 5};
    MatchResult result = matchOrders(a, b);
     result = matchOrders(a, b);

    cout << "Matched Quantity: " << result.qtyFilled << endl;
    cout << "Remaining Order A Quantity: " << a.qty << endl;
    cout << "Remaining Order B Quantity: " << b.qty << endl;







}


// everything in c++ i copy unless you use &
// deep copy vs shallow copy
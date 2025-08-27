#include <iostream>
using namespace std;

struct Order {
    int price;
    int quantity;
};




void totalQuantity(Order orders[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += orders[i].quantity;
    }
    cout << "Total Quantity: " << total << endl;
}

int main() {
    Order orders[] = {
        {100, 2},
        {150, 5},
        {200, 3}
    };

    
    int size = sizeof(orders) / sizeof(orders[0]);
    totalQuantity(orders, size);
}
#include<iostream> 
using namespace std;

void f(int *x){
    x = nullptr;
}


int main() {
    int* y = new int;
    *y = 8;
   
}
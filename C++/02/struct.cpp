#include<iostream>
#include<math.h>
using namespace std;


struct Point{
    int x,y;
};

double getDistance(Point a, Point b){
    
    double euclidean = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    return euclidean;
}
// manhtan -- without suaring root
// after square root -- duclidean
// Point a {0,0} -- constructor 

int main(){
    Point p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    cout << getDistance(p1, p2) << endl;
    return 0;
}
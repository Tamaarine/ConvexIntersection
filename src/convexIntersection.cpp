#include <iostream>
#include <string>
#include "polygon.h"
#include "utils.h"

using namespace std;

int main() {
    Point p1;
    p1.y = 19;
    
    Point p2(1,2);

    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
    std::cout << subtract(p1, p2) << "\n";
    
    Polygon poly1;
    Polygon poly2;
    
    vector<Point> list1 = {Point(0,2), Point(0,0), Point(1.5,0), Point(1.5,2)};
    vector<Point> list2 = {Point(2,1), Point(2,0), Point(1,0), Point(1,1)};
    
    poly1.vertices = list1;
    poly2.vertices = list2;
    
    convexIntersect(poly1, poly2);
    
    return 0;
}
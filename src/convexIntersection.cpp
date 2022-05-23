#include <iostream>
#include <string>
#include <vector>
#include "polygon.h"
#include "utils.h"

using namespace std;

int main() {
    Point p1;
    p1.y = 19;
    
    Point p2(1,2);

    cout << p1 << "\n";
    cout << p2 << "\n";
    cout << subtract(p1, p2) << "\n";
    
    Polygon poly1;
    Polygon poly2;
    
    vector<Point> list1 = {Point(2,3), Point(-0.267,1.777), Point(0.68,-0.60), Point(3.35,-0.49), Point(5.53,1.1), Point(3.7,2.7)};
    vector<Point> list2 = {Point(2.86,3.3), Point(2.38,1.71), Point(4.1,0.87), Point(5.2,1.77), Point(5.92,3.12), Point(3.8,3.44)};
    
    poly1.vertices = list1;
    poly2.vertices = list2;
    
    vector<Point> intersections;
    
    convexIntersect(poly1, poly2, intersections);
    
    Polygon inters;
    inters.vertices = intersections;
    
    cout << "the final intersection\n";
    cout << inters;
    
    return 0;
}
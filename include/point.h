#ifndef POINT
#define POINT

#include <iostream>

class Point {
    public:
    
    float x, y;
    
    Point(float x1, float y1) {
        x = x1;
        y = y1;
    }
    
    Point() {
        x = 0;
        y = 0;
    }
};

Point subtract(Point &p1, Point &p2);

std::ostream& operator<<(std::ostream &stream, const Point &a);

#endif 
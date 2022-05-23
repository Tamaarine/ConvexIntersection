#include <iostream>
#include <point.h>

Point subtract(Point &p1, Point &p2) {
    Point ret; 
    ret.x = p1.x - p2.x;
    ret.y = p1.y - p2.y;
    return ret;
}

std::ostream& operator<<(std::ostream &stream, const Point &a) {
    return stream << "X: " << a.x << " Y: " << a.y;
}

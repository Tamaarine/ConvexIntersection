#ifndef POLYGON
#define POLYGON

#include "point.h"
#include <vector>

class Polygon {
    public:
    std::vector<Point> vertices;
};

/**
 * Return the size of the number of vertices in this polygon
 */
int size(const Polygon &p);

std::ostream& operator<<(std::ostream &stream, const Polygon &a);

#endif
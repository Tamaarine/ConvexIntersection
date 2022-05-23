#include "polygon.h"
#include <string>

using namespace std;

int size(const Polygon &p) {
    return p.vertices.size();
}

std::ostream& operator<<(std::ostream &stream, const Polygon &a) {
    stream << "Polygon: ";
    for(auto p: a.vertices) {
        stream << p.x << " " << p.y << ",  ";
    }
    return stream << "\n";
}
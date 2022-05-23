#include "polygon.h"
#include <string>
#include <iomanip>

using namespace std;

int size(const Polygon &p) {
    return p.vertices.size();
}

std::ostream& operator<<(std::ostream &stream, const Polygon &a) {
    stream << "Polygon: \n";
    int minx, miny;
    minx = 0, miny = 0;
    
    for(auto p: a.vertices) {
        int lenx = to_string(p.x).find(".");
        int leny = to_string(p.y).find(".");
        
        minx = lenx > minx ? lenx : minx;
        miny = leny > miny ? leny : miny;
    }
    int precision = 3;
    minx += precision + 1;
    miny += precision + 1;
    for (auto p: a.vertices) {
        stream << "X: " << setw(minx) << setprecision(3) << p.x << " Y: " << setw(miny) << setprecision(3) << p.y << endl;
    }
    return stream;
}
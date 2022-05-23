#ifndef UTILS
#define UTILS

#include "point.h"
#include "polygon.h"
#include <vector>

#define Pin 0
#define Qin 1
#define Unknown 2 

/**
 * Return the quadrilateral area between vector ab and ac.
 * Used for left tests
 */
float area2(Point &a, Point &b, Point &c);

/**
 * Return the sign of the area2
 */
float areaSign(Point &a, Point &b, Point &c);

/**
 * Whether the three points are collinear or not 
 */
bool collinear(Point &a, Point &b, Point &c);

/**
 * Whether point c is in between point a & b 
 */
bool between(Point &a, Point &b, Point &c);

/**
 * The special case for segSegIntersection.
 */
char parallelInt(Point &a, Point &b, Point &c, Point &d, Point &p);

/**
 * Given segment ab and cd, find the point of intersection p between
 * the two segments. Return the point of intersection in p and a char
 *      'e': The segment collinearly overlap, sharing a point.
 *      'v': An endpoint (vertex) of one segment is on the other segment,
 *          but 'e' doesn't hold.
 *      '1': The segments intersect properly (i.e., they share a point and
 *          neither 'v' nor 'e' holds).
 *      '0': The segments do not intersect (i.e., they share no points).
 */
char segSegInt(Point &a, Point &b, Point &c, Point &d, Point &p);

int inOut(Point &p, int inflag, int aHB, int bHA, std::vector<Point> &intersections);

/**
 * Return the next vertex to consider
 */
int advance(int a, int * aa, int n, bool inside, Point &v, std::vector<Point> &intersections);

/**
 * The heart of the code where it does the double advancing segments
 * in order to find the intersected regions
 */
void convexIntersect(Polygon &P, Polygon &Q, std::vector<Point> &intersections);

#endif 
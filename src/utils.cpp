#include "utils.h"

/**
 * Return the quadrilateral area between vector ab and ac.
 * Used for left tests
 */
float area2(Point &a, Point &b, Point &c) {
    return (b.x - a.x) * (c.y - a.y) -
           (c.x - a.x) * (b.y - a.y);
}

/**
 * Return the sign of the area2
 */
float areaSign(Point &a, Point &b, Point &c) {
    float a2 = area2(a, b, c);
    
    if (a2 > 0.5) return 1;
    else if (a2 < -0.5) return -1;
    else return 0 ;
}

/**
 * Whether the three points are collinear or not 
 */
bool collinear(Point &a, Point &b, Point &c) {
    return area2(a, b, c) == 0;
}

/**
 * Whether point c is in between point a & b 
 */
bool between(Point &a, Point &b, Point &c) {
    if (!collinear(a, b, c)) return false;
    
    if (a.x != b.x)
        return (a.x <= c.x && c.x <= b.x) || 
               (a.x >= c.x && c.x >= b.x);
    else
        return (a.y <= c.y && c.y <= b.y) ||
               (a.y >= c.y && c.y >= b.y);
}

/**
 * The special case for segSegIntersection.
 */
char parallelInt(Point &a, Point &b, Point &c, Point &d, Point &p) {
    if (!collinear(a, b, c)) return '0';
    
    if (between(a, b, c)) {
        p.x = c.x;
        p.y = c.y;
        return 'e';
    }
    if (between(a, b, d)) {
        p.x = d.x;
        p.y = d.y;
        return 'e';
    }
    if (between(c, d, a)) {
        p.x = a.x;
        p.y = a.y;
        return 'e';
    }
    if (between(c, d, b)) {
        p.x = b.x;
        p.y = b.y;
        return 'e';
    }
    return '0';
}

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
char segSegInt(Point &a, Point &b, Point &c, Point &d, Point &p) {
    double s, t;        // Two parameters of the parametric equations
    double num, denom;  // Numerator and denominator of equation
    char code = '?';    // Return code for the function
    
    denom = a.x * (double)( d.y - c.y ) +
            b.x * (double)( c.y - d.y ) +
            d.x * (double)( b.y - a.y ) +
            c.x * (double)( a.y - b.y );
    
    if (denom == 0)
        return parallelInt(a, b, c, d, p);
    
    num = a.x * (d.y - c.y) + 
          c.x * (a.y - d.y) + 
          d.x * (c.y - a.y);
          
    if (num == 0 || num == denom) 
        code = 'v';
    s = num / denom;
    
    num = -(a.x * (c.y - b.y) + 
           b.x * (a.y - c.y) + 
           c.x * (b.y - a.y));
           
    t = num / denom;
    
    if (0 < s && s < 1 && 0 < t && t < 1)
        code = '1';
    else if (0 > s || s > 1 || 0 > t || t > 1)
        code = '0';
    
    p.x = a.x + s * (b.x - a.x);
    p.y = a.y + s * (b.y - a.y);
    
    return code;
}

int inOut(Point &p, int inflag, int aHB, int bHA) {
    std::cout << p << " lineto\n";
    
    if (aHB > 0) return Pin;
    else if  (bHA > 0) return Qin;
    else return inflag;
}

/**
 * Return the next vertex to consider
 */
int advance(int a, int * aa, int n, bool inside, Point &v) {
    if (inside) {
        std::cout << v << " lineto\n";
    }
    (*aa)++;
    return (a + 1) % n;
}

/**
 * The heart of the code where it does the double advancing segments
 * in order to find the intersected regions
 */
void convexIntersect(Polygon &P, Polygon &Q) {
    int a, b;
    int a1, b1;
    Point A, B;
    int cross;
    int bHA, aHB;
    Point origin(0, 0);
    Point p;
    // Point q;
    int inflag;
    int aa, ba; 
    bool firstPoint;
    Point p0;
    int code;
    
    a = 0; b = 0; aa = 0; ba = 0;
    inflag = Unknown; firstPoint = true;
    
    int n = size(P);
    int m = size(Q);
    
    do {
        a1 = (a + n - 1) % n;
        b1 = (b + m - 1) % m;
        
        A = subtract(P.vertices.at(a), P.vertices.at(a1));
        B = subtract(P.vertices.at(b), P.vertices.at(b1));
        
        cross = areaSign(origin, A, B);
        aHB = areaSign(Q.vertices.at(b1), Q.vertices.at(b), P.vertices.at(a));
        bHA = areaSign(P.vertices.at(a1), P.vertices.at(a), Q.vertices.at(b));
        
        code = segSegInt(P.vertices.at(a1), P.vertices.at(a), Q.vertices.at(b1), Q.vertices.at(b), p);
        if ( code == '1' || code == 'v' ) {
            if ( inflag == Unknown && firstPoint ) {
                aa = ba = 0;
                firstPoint = false;
                p0.x = p.x; p0.y = p.y;
                std::cout << p0 << " moveto\n";
            }
            inflag = inOut(p, inflag, aHB, bHA );
        }

        if (cross >= 0)
        {
            if (bHA > 0)
                a = advance(a, &aa, n, inflag == Pin, P.vertices.at(a));
            else
                b = advance(b, &ba, m, inflag == Qin, Q.vertices.at(b));
        }
        else /* if ( cross < 0 ) */
        {
            if (aHB > 0)
                b = advance(b, &ba, m, inflag == Qin, Q.vertices.at(b));
            else
                a = advance(a, &aa, n, inflag == Pin, P.vertices.at(a));
        }
    } while ( ((aa < n) || (ba < m)) && (aa < 2*n) && (ba < 2*m) );
    
    if (!firstPoint)
        std::cout << p0 << " lineto\n";
}
# <a name="intro"></a>Description
This project compiles a program which will be able to read in points for two convex polygons and proceed to
produce the intersection polygon between the two polygons. 

Please note that the input polygons must either be both in ccw or both in cw! Otherwise, the algorithm
that is used for finding the intersections will be confused and wouldn't be able to find the
correct intersections. 

# <a name="how"></a>Compiling Project
* `make`
* `bin/convexIntersect`
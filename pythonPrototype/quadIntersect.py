from matplotlib import pyplot as py

INTERSECTION = []
poly1 = True

class Point():
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def __str__(self):
        return f"Point {self.x} {self.y}"
    def __repr__(self):
        return f"Point {self.x} {self.y}"
    
    def subtract(a, b):
        return Point(a.x - b.x, a.y - b.y)
            
class Polygon():
    def __init__(self):
        '''Polygon is a list of Points'''
        self.polygon = []
        
    def loadpoints(self, file=None, list=None):
        if file is not None:
            with open(file, 'r') as f:
                for line in f:
                    splitted = line.split(',')
                    point = Point(float(splitted[0]), float(splitted[1]))
                    self.polygon.append(point)
        elif list is not None:
            pointList = [] 
            for i in range(len(list) // 2):
                point = Point(list[2*i], list[2*i + 1])
                pointList.append(point)
            self.polygon = pointList
        
    def __str__(self):
        out = ""
        for point in self.polygon:
            out += f"{point.x} {point.y}, "
        return out
            
    def __repr__(self):
        out = ""
        for point in self.polygon:
            out += f"{point.x} {point.y}, "
        return out
        
    def size(self):
        return len(self.polygon)
    
def onmouseclick(event):
    '''Event handler for inputting the points and storing it into the global list "points" '''
    global ax
    ix, iy = event.xdata, event.ydata
    if ix and iy:
        toAppend = Point(ix, iy)
        if poly1:
            polygon1.polygon.append(toAppend)
            ax.plot(ix, iy, marker='o', color='black')
            py.show()
        else:
            polygon2.polygon.append(toAppend)
            ax.plot(ix, iy, marker='o', color='orange')
            py.show()

def onkeypress(event):
    global ax, gw, poly1
    
    if event.key == ' ':
        '''Carry out the gift-wrapping stop point collection from mouse if exists '''
        poly1 = False
        print("flipped")
    elif event.key == 'c':
        convexIntersect(polygon1, polygon2)
    
        xs = [ele.x for ele in polygon1.polygon]
        ys = [ele.y for ele in polygon1.polygon]
        
        py.plot(xs, ys)
        
        xs = [ele.x for ele in polygon2.polygon]
        ys = [ele.y for ele in polygon2.polygon]
        
        py.plot(xs, ys, color='r')
        
        xs = [ele.x for ele in INTERSECTION]
        ys = [ele.y for ele in INTERSECTION]
        
        py.plot(xs, ys, color='blue')
        
        py.show()

    
def area2(a: Point, b: Point, c: Point):
    return (b.x - a.x) * (c.y - a.y) - \
           (c.x - a.x) * (b.y - a.y)

def areaSign(a: Point, b: Point, c: Point):
    '''Return the sign of the determinant'''
    a2 = area2(a, b, c)
    
    if a2 > 0.5:
        return 1
    elif a2 < -0.5:
        return -1
    else:
        return 0 
    
def collinear(a, b, c):
    return area2(a, b, c) == 0

def between(a, b, c):
    if not collinear(a, b, c): return False
    
    if a.x != b.x:
        return (a.x <= c.x and c.x <= b.x) or \
               (a.x >= c.x and c.x >= b.x)  
    else:
        return (a.y <= c.y and c.y <= b.y) or \
               (a.y >= c.y and c.y >= b.y)  

def parallelInt(a, b, c, d):
    if not collinear(a, b, c):
        return '0', Point(-1, -1)
    
    if between(a, b, c):
        return 'e', c 
    if between(a, b, d):
        return 'e', d
    if between(c, d, a):
        return 'e', a
    if between(c, d, b):
        return 'e', b
    return '0', Point(-1, -1)

def segSegInt(a, b, c, d):
    '''
    Given segment ab and cd, find the point of intersection p between
    the two segments. Return the point of intersection and a char
        'e': The segments collinearly overlap, sharing a point.
        'v': An endpoint (vertex) of one segment is on the other segment,
            but 'e' doesn't hold.
        '1': The segments intersect properly (i.e., they share a point and
            neither 'v' nor 'e' holds).
        '0': The segments do not intersect (i.e., they share no points).
    '''
    s, t = 0, 0 # Two parameters of the parametric equations
    num, denom = 0, 0 # Numerator and denominator of equation
    code = '?'
    
    denom = a.x * (d.y - c.y) + \
            b.x * (c.y - d.y) + \
            d.x * (b.y - a.y) + \
            c.x * (a.y - b.y) 
    
    # Parallel handle separately
    if denom == 0:
        return parallelInt(a, b, c, d)
    
    num = a.x * (d.y - c.y) + \
          c.x * (a.y - d.y) + \
          d.x * (c.y - a.y)    
    if num == 0 or num == denom:
        code = 'v'
    s = num / denom
    
    num = -(a.x * (c.y - b.y) + \
           b.x * (a.y - c.y) + \
           c.x * (b.y - a.y)    )
    if num == 0 or num == denom:
        code = 'v'
    t = num / denom
    
    if 0 < s and s < 1 and 0 < t and t < 1:
        code = '1'
    elif 0 > s or s > 1 or 0 > t or t > 1:
        code = '0'
    
    p = Point(a.x + s * (b.x - a.x),
              a.y + s * (b.y - a.y)) 
              
    return code, p 

def inOut(p, inflag, aHB, bHA):
    print(f"{p.x} {p.y} lineto")
    INTERSECTION.append(Point(p.x, p.y))
    
    if aHB > 0:
        return 0
    elif bHA > 0:
        return 1
    else:
        return inflag
        
def advance(a, n, inside, v):
    if inside:
        print(f"{v.x} {v.y} lineto")
        INTERSECTION.append(Point(v.x, v.y))
        
    return (a + 1) % n
    
def convexIntersect(p: Polygon, q: Polygon) -> Polygon:
    a, b = 0, 0                         # Indices for P and Q
    a1, b1 = 0, 0                       # a1 and b1, edges after a, b 
    A, B = Point(-1, -1), Point(-1, -1) # Directed edge on P and Q
    cross = 0                           # Sign of z-component for A x B
    bHA, aHB = 0, 0                     # b in H(a); a in H(b)
    origin = Point(0, 0)
    # p = Point(-1, -1)                   # Point of interesection 
    # q = Point(-1, -1)                   # Second point of intersection
    inflag = 2
    aa, ba = 0, 0                       # Used for advances on a & b
    firstPoint = True                   # Used for initialization
    p0 = Point(-1, -1)                  # Storing first point 
    code = '0'                          # Return code for segSegInt
    
    n = p.size()
    m = q.size()
    
    p = p.polygon
    q = q.polygon
    
    while True: 
        a1 = (a + n - 1) % n
        b1 = (b + m - 1) % m
        
        A = Point.subtract(p[a], p[a1])
        B = Point.subtract(q[b], q[b1])
        
        cross = areaSign(origin, A, B)
        aHB = areaSign(q[b1], q[b], p[a]) # Left tests
        bHA = areaSign(p[a1], p[a], q[b]) # Left tests
        
        code, retp = segSegInt(p[a1], p[a], q[b1], q[b])
        if code == '1' or code == 'v':
            if inflag == 2 and firstPoint:
                aa = ba = 0
                firstPoint = False 
                p0.x = retp.x
                p0.y = retp.y
                print(f"{p0.x} {p0.y} moveto")
            inflag = inOut(retp, inflag, aHB, bHA)
        
        # Generic cases for advancing the segments
        if cross >= 0:
            if bHA > 0:
                a = advance(a, n, inflag == 0, p[a])
                aa += 1
            else:
                b = advance(b, m, inflag == 1, q[b])
                ba += 1
        else:
            if aHB > 0:
                b = advance(b, m, inflag == 1, q[b])
                ba += 1
            else:
                a = advance(a, n, inflag == 0, p[a])
                aa += 1
        if not (aa < n) and not (ba < m) or not aa < 2*n or not ba < 2*m:
            break
    
    if not firstPoint:
        print(f"{p0.x} {p0.y} lineto")
        INTERSECTION.append(Point(p0.x, p0.y))
        
if __name__ == "__main__":
    fig, ax = py.subplots(1, 1)
    
    cid = fig.canvas.mpl_connect('button_press_event', onmouseclick)
    fig.canvas.mpl_connect('key_press_event', onkeypress)
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 10)
    
    polygon1 = Polygon()
    polygon2 = Polygon()
    
    py.show()
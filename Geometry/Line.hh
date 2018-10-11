#include "Point.hh"

struct Line {
  Ptype a, b, c;
  Line(const Point&p, const Point&q) {
    a = q.y-p.y, b = p.x-q.x;
    // auto g = __gcd(a, b);
    // a /= g, b /= g;
    c = -(a*p.x+b*p.y);
  }
  Line (const Ptype&aa=0, const Ptype&bb=0, const Ptype&cc=0) :
    a(aa), b(bb), c(cc) { }
  inline Ptype fxval(const Point&p) const &
  { return a*p.x + b*p.y + c; }
  inline Ptype dist2(const Point&p) const& {
    Ptype fx = fxval(p);
    return (fx * fx) / (a*a+b*b);
  }
  Ftype distance(const Point &p) const &
  { return sqrt(dist2(p)); }
};
ostream& operator<<(ostream &os, const Line &l)
{ return os<<'['<<l.a<<" * x + "<<l.b<<" * y + "<<l.c<<" =0]"; }

/* Projection formula : k=-1 for foot of perpendicular,
   -2 for reflection about line. */
Point projection(const Point&p, const Line&line, const Ftype &k=-1.) {
  auto temp = k*line.fxval(p)/(line.a*line.a+line.b*line.b);
  return Point(p.x + line.a*temp, p.y + line.b*temp);
} // Extend to 3D

/* Line-Line cut points. Returns <number_of_points, point_if_unique> */
tuple< int , Point > cut(const Line &A, const Line &B) {
  int cutPoints = 0; Point ret;
  Ptype det = A.a*B.b - A.b*B.a;
  if( abs( det ) <= eps ) {
    cutPoints = 0; // Degenerate case.
    if( abs( A.a*B.c - A.c*B.a ) <= eps )
      cutPoints = -1; // Infinitely many.
  } else {
    cutPoints = 1; // Unique point of intersection.
    ret.x = ( A.b*B.c - A.c*B.b ) / det ;
    ret.y = ( A.c*B.a - A.a*B.c ) / det ;
  }
  return tie(cutPoints , ret);
}

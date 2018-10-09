#include "../Header.hh"

using Ptype = long long;   // discrete metrics
Ptype eps = (Ptype)(1e-6); // fine tune
using Ftype = long double; // all other metrics

struct Point {
  Ptype x, y;
  Point(Ptype xx=0, Ptype yy=0) : x(xx), y(yy) {}
  inline Ptype norm2() const& {return x*x+y*y;}
  Ftype norm() const& {return sqrt(norm2()); }
  Ftype arg() const& {return atan2(y, x);}
};
Point operator+(const Point&p, const Point&q)
{ return Point(p.x+q.x, p.y+q.y); }
Point operator-(const Point&p, const Point&q)
{ return Point(p.x-q.x, p.y-q.y); }
Point operator*(const Point &p, const Ptype &k)
{ return Point(k*p.x,k*p.y); }
Point operator/(const Point &p, const Ptype &k)
{ return Point(p.x/k,p.y/k); }
Ptype operator*(const Point &p, const Point &q)
{ return p.x*q.y - q.x*p.y; }
Ptype operator^(const Point &p, const Point &q)
{ return p.x*q.x + p.y*q.y; }
bool operator==(const Point&p, const Point&q)
{ return abs(p.x-q.x) <= eps and abs(p.y-q.y) <= eps; }
ostream& operator<<(ostream &out, const Point&p)
{ return out << '[' << p.x << ' ' << p.y << ']'; }

/* Returns twice the signed area. */
Ptype signedAreax2(const vector<Point> &v) {
  Ptype ret = 0;
  for(size_t i=0, j=v.size()-1; i<v.size(); j=i++)
    ret += (v[i].x-v[j].x)*(v[i].y+v[j].y);
  return ret;
}

/* First translate to new origin, then rotate by theta. */
Point affineTransform (const Point &point,
                       const Point &pivot, const Ftype &theta) {
  Point t = point - pivot; Ftype C = cos(theta), S = sin(theta);
  return Point(t.x*C-t.y*S, t.x*S+t.y*C) ;
} // PType must be float

#pragma once
#include "Point.hh"

#define Ptype ll

template<typename T>
struct Line {
  T a, b, c;
  Line(const Point<T>&p, const Point<T>&q) {
    a = q.y-p.y, b = p.x-q.x;
    // auto g = __gcd(a, b);
    // a /= g, b /= g;
    c = -(a*p.x+b*p.y);
  }
  Line (const T&aa=0, const T&bb=0, const T&cc=0) :
    a(aa), b(bb), c(cc) { }
  inline T fxval(const Point<T>&p) const { return a*p.x + b*p.y + c; }
  Point<T> dir() const { return Point<T>(a, b); }
};

template<typename T> ostream& operator<<(ostream &os, const Line<T>&l)
{ return os<<'['<<l.a<<" * x + "<<l.b<<" * y + "<<l.c<<" =0]"; }

template<typename U, typename V>
long double dist2(const Line<U>&line, const Point<V>&p)
{ long double fx = line.fxval(p); return (fx * fx) / line.dir().norm2(); }
template<typename U, typename V>
long double dist(const Line<U>&line, const Point<V>&p)
{ long double fx = line.fxval(p); return abs(fx) / line.dir().norm(); }
// { return sqrt( dist2(line, p) ); }

/* Projection formula : k=-1 for foot, -2 for reflection. */
template<typename T, typename V, typename W=int> Point<T> projection
(const Point<T>&p, const Line<V>&line, const W&k=-1) {
  T temp = line.fxval(p)/((T) line.dir().norm2());
  return Point<T>(p.x + line.a * temp * k, p.y + line.b * temp * k);
} // Extend to 3D.

#pragma once
#include "../Header.hh"

template<typename T>
struct Point {
  T x, y;
  Point() : x(0), y(0) {}
  Point(const T&_x, const T&_y) : x(_x), y(_y) {}
  inline T norm2() const& { return x*x+y*y; }
  inline auto norm() -> decltype(sqrt(norm2())) {return sqrt(norm2());}
  inline auto arg()  -> decltype(atan2(y, x))   {return atan2(y, x);}
};

/* Sums. */
template<typename T> Point<T> operator+(const Point<T>&p, const Point<T>&q)
{ return Point<T>(p.x+q.x, p.y+q.y); }
template<typename T> Point<T> operator-(const Point<T>&p, const Point<T>&q)
{ return Point<T>(p.x-q.x, p.y-q.y); }

/* Scalar products. */
template<typename T, typename F> Point<T> operator*(const Point<T>&p, const F&k)
{ return Point<T>(k*p.x,k*p.y); }
template<typename T, typename F> Point<T> operator*(const F&k, const Point<T>&p)
{ return Point<T>(k*p.x,k*p.y); }
template<typename T, typename F> Point<T> operator/(const Point<T>&p, const F&k)
{ return Point(p.x/k,p.y/k); }

/* Vector products. */
template<typename T> T operator*(const Point<T>&p, const Point<T>&q)
{ return p.x*q.y - q.x*p.y; }
template<typename T> T operator^(const Point<T>&p, const Point<T>&q)
{ return p.x*q.x + p.y*q.y; }

/* Comparators. */
template<typename T> inline bool operator< (const Point<T>&p, const Point<T>&q)
{ return p.x != q.x ? p.x < q.x : p.y < q.y; }
template<typename T> inline bool operator==(const Point<T>&p, const Point<T>&q)
{ return (p.x == q.x) and (p.y == q.y); } // Don't use == for floats.

/* Debugger. */
template<typename T> ostream& operator<<(ostream &out, const Point<T>&p)
{ return out << '[' << p.x << ' ' << p.y << ']'; }

/* Returns twice the signed area. */
template <typename T> T signedAreax2(const vector< Point<T> > &v) {
  T ret = 0;
  for(size_t i=0, j=v.size()-1; i<v.size(); j=i++)
    ret += (v[i].x-v[j].x)*(v[i].y+v[j].y);
  return ret;
}

/* Rotate by theta around pivot. */
template<typename T, typename F> Point<T> affineTransform
(const Point<T>&point, const Point<T> &pivot, const F &theta) {
  auto t = point - pivot; auto C = cos(theta), S = sin(theta);
  return pivot + Point<T>(t.x*C-t.y*S, t.x*S+t.y*C) ;
} // T must be float.

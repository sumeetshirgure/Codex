#pragma once
#include "Point.hh"
#include "Line.hh"

#define EPS (1e-7L)

/* Line-Line cut points. Returns <number_of_points, point_if_unique> */
template<typename T> tuple<int, Point<T>>
cut(const Line<T> &A,const Line<T> &B) {
  int cutPoints = 0; Point<T> ret;
  T det = A.a*B.b - A.b*B.a;
  if( abs( det ) <= EPS ) {
    cutPoints = 0; // Degenerate case.
    if( abs( A.a*B.c - A.c*B.a ) <= EPS ) cutPoints = -1; // Infinitely many.
  } else {
    cutPoints = 1; // Unique point of intersection.
    ret.x = ( A.b*B.c - A.c*B.b ) / det ;
    ret.y = ( A.c*B.a - A.a*B.c ) / det ;
  }
  return tie(cutPoints , ret);
}

/* Line segment intersection. */
template<typename T> tuple<int, Point<T>, Point<T>> cut
(Point<T> u, Point<T> v, Point<T> s, Point<T> t) {
  int cuts = 0; Point<T> z1, z2;
  tie(cuts, z1) = cut(Line<T>(u, v), Line<T>(s, t));
  if( cuts == 0 ) return tie(cuts, z1, z2); // parallel
  if( cuts == -1 ) { // coinciding
    if( v < u ) swap(u, v);
    if( t < s ) swap(u, v);
    z1.x = max(u.x, s.x), z1.y = max(u.y, s.y);
    z2.x = min(v.x, t.x), z2.y = min(v.y, t.y);
    if( z2 < z1 ) cuts = 0;
    return tie(cuts, z1, z2);
  }
  auto du = z1-u, dv = z1-v, ds = z1-s, dt = z1-t; // unique
  if( (du ^ dv) > 0 or (ds ^ dt) > 0 ) cuts = 0; // but outside
  return tie(cuts, z1, z2);
}

/* Line - circle cut points */
template<typename T> tuple<int, Point<T>, Point<T>>
cut(const Line<T> &line, const Point<T> &center, const T& radius) {
  int cuts = 0;
  Point<T> p1, p2;
  T distance = dist(line, center);
  if( abs(distance - radius) <= EPS ) {
    cuts = 1;
    p1 = projection(center, line, -1);
  } else if( distance > radius ) {
    cuts = 0;
  } else {
    cuts = 2;
    Point<T> foot = projection(center, line, -1);
    Point<T> delta(line.b, -line.a); delta = delta / delta.norm();
    T lat = sqrt( radius*radius - distance*distance );
    delta = lat * delta ; p1 = foot + delta, p2 = foot - delta;
  }
  return tie(cuts, p1, p2);
}



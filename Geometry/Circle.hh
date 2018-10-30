#pragma once
#include "Point.hh"
#include "Cuts.hh"

template<typename T> Line<T> halfline(const Point<T> &p, const Point<T> &q) {
  auto mpt = (p+q)/2, dir = q-p;
  Line<T> line(dir.x, dir.y, 0); line.c = -line.fxval(mpt);
  return line;
}

template<typename T> tuple<T, Point<T>> make_circle
(const Point<T> &r, const Point<T> &s, const Point<T> &t) {
  if( abs((s-r)*(t-r)) <= EPS ) return make_tuple(-1, Point<T>());
  auto l1 = halfline(r, s), l2 = halfline(s, t);
  Point<T> center; tie(ignore, center) = cut(l1, l2);
  T radius = (center-s).norm();
  return tie(radius, center);
}

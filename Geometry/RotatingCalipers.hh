#pragma once
#include "Point.hh"

/* Rotating calipers to find antipodal points. */
template<typename T> void antipodal_pairs(const vector<Point<T>> &p) {
  int n = p.size();
  if( n == 1 ) return;
  for(int i=0, j=n-1, u=0, v=1; i<n; j=i++) {
    auto base = p[i] - p[j];
    for(; base * (p[v]-p[u]) > 0; u=v++) if( v == n ) v = 0;
    // Point p[u] is the first antipodal point w.r.t base.
    // Change loop invariant to `base * (p[v]-p[u]) >= 0' to get
    // all points...
  }
}

/* Example cases : diameter and width of convex polygons. */
template<typename T> T diameter(const vector<Point<T>> &p) {
  int n = p.size();
  if( n == 1 ) return 0;
  T dia = 0;
  for(int i=0, j=n-1, u=0, v=1; i<n; j=i++) {
    Point base = p[i] - p[j];
    for(; base * (p[v]-p[u]) > 0; u=v++) if( v == n ) v = 0;
    setMax(dia, (p[u]-p[i]).norm());
    setMax(dia, (p[u]-p[j]).norm());
  }
  return dia;
}

template<typename T> T width(const vector<Point<T>>&p) {
  int n = p.size();
  if( n == 1 ) return 0;
  T width = -1;
  for(int i=0, j=n-1, u=0, v=1; i<n; j=i++) {
    auto base = p[i] - p[j];
    for(; base * (p[v]-p[u]) > 0; u=v++) if( v == n ) v = 0;
    T curWidth = (base * (p[u]-p[j])) / base.norm();
    if( width < 0 ) width = curWidth;
    else setMin(width, curWidth);
  }
  return width;
}

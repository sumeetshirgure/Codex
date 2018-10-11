#pragma once
#include "Point.hh"

using Polygon = vector<Point>; // Convex polygons.

/* Rotating calipers to find antipodal points. */
void antipodal_pairs(const Polygon &p) {
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
Ftype diameter(const Polygon&p) {
  int n = p.size();
  if( n == 1 ) return 0;
  Ftype dia = 0;
  for(int i=0, j=n-1, u=0, v=1; i<n; j=i++) {
    Point base = p[i] - p[j];
    for(; base * (p[v]-p[u]) > 0; u=v++) if( v == n ) v = 0;
    setMax(dia, (p[u]-p[i]).norm());
    setMax(dia, (p[u]-p[j]).norm());
  }
  return dia;
}

Ftype width(const Polygon&p) {
  int n = p.size();
  if( n == 1 ) return 0;
  Ftype width = -1;
  for(int i=0, j=n-1, u=0, v=1; i<n; j=i++) {
    auto base = p[i] - p[j];
    for(; base * (p[v]-p[u]) > 0; u=v++) if( v == n ) v = 0;
    Ftype curWidth = (base * (p[u]-p[j])) / base.norm();
    if( width < 0 ) width = curWidth;
    else setMin(width, curWidth);
  }
  return width;
}

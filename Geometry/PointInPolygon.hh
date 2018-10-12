#pragma once
#include "Point.hh"

/* Winding number of a polygon around a point. Assumes point not on polygon. */
template<typename T> 
int winding_number(const Point<T>&p, const vector<Point<T>>&v) {
  int n = v.size(), wn = 0;
  for(int j=n-1, i=0; i<n; j=i++) {
    if( v[j].y <= p.y and v[i].y >  p.y and (v[i]-v[j])*(p-v[j]) > 0 ) wn++;
    if( v[j].y >  p.y and v[i].y <= p.y and (v[i]-v[j])*(p-v[j]) < 0 ) wn--;
  }
  return wn;
} // Self intersecting polygons are okay!

/* Answers point in polygon query: O(n). */
template<typename T>
int point_in_polygon(const Point<T>&p, const vector<Point<T>>&v) {
  int n = v.size();
  for(int j=n-1, i=0; i<n; j=i++) {
    if( p == v[i] ) return 0; // Point coincides.
    Point<T> pi = p - v[i], pj = p - v[j];
    if( (pi*pj) == 0 and (pi^pj) <= 0 ) return 0; // Point on segment.
  }
  if( winding_number(p, v) == 0 ) return -1;
  return 1; // Report -ve winding numbers separately.
} // 0 : on, +1 : out, -1 : in


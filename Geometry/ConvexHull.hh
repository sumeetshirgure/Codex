#pragma once
#include "Point.hh"

/* Andrew's monotone chain algorithm.*/
template<typename T> vector<Point<T>> convex_hull(vector<Point<T>> &v) {
  if( v.size() <= 1 ) return v;
  vector<Point<T>> hull(v.size()+1);
  sort(v.begin(), v.end(), [&](const Point<T>&p, const Point<T>&q) {
                             return p.x!=q.x?p.x<q.x:p.y<q.y; });
  size_t hsz = 0;
  for(int phase=0; phase<2; phase++) {
    size_t lim = hsz;
    for(auto &p: v) {
      // change to < 0 for allowing collinear points on hull
      // set hull maxsize to 2 * v.size() + 1 in that case
      while(hsz>=lim+2 and ((hull[hsz-1]-hull[hsz-2])*(p-hull[hsz-1]))<=0)
        hsz--;
      hull[hsz++] = p;
    }
    hsz--; // covered by the other phase
    if( phase == 0 ) reverse(v.begin(), v.end());
  }
  hull.resize(hsz);
  return hull;
}

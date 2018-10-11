#include "Point.hh"

using Polygon = vector<Point>;

/* Andrew's monotone chain algorithm.*/
Polygon convex_hull(Polygon &v) {
  if( v.size() <= 1 ) return v;
  Polygon hull(v.size()+1);
  sort(v.begin(), v.end(), [&](const Point&p, const Point&q) {
                             return p.x!=q.x?p.x<q.x:p.y<q.y; });
  size_t hsz = 0;
  for(int phase=0; phase<2; phase++) {
    size_t lim = hsz;
    for(auto &p: v) {
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

#pragma once
#include "Point.hh"

template<typename T>
void dnc(size_t lx, size_t rx,
         T &opt, Point<T> &_p, Point<T> &_q, vector<Point<T>> &v) {
  if( rx - lx == 1 ) return;
  auto mid = (lx + rx)>>1;
  T xmid = v[mid].x;
  dnc(lx, mid, opt, _p, _q, v);
  dnc(mid, rx, opt, _p, _q, v);
  inplace_merge(v.begin()+lx, v.begin()+mid, v.begin()+rx,
                [&](const Point<T>&p, const Point<T>&q) {
                  return p.y!=q.y?p.y<q.y:p.x<q.x;} );
  vector< Point<T> > a;
  for(size_t i=lx; i<rx; i++)
    if( (v[i].x-xmid) * (v[i].x-xmid) <= opt )
      a.emplace_back(v[i]); // 2 * opt strip
  auto temp = opt;
  for(int i=0; i<(int)a.size(); i++)
    for(int j=i-1; j>=0 and (a[i].y-a[j].y)*(a[i].y-a[j].y) <= opt; j--)
      if( smin(temp, (a[i]-a[j]).norm2()) ) _p=a[i], _q=a[j]; // O(1)
  opt = temp;
}

template<typename T>
pair<Point<T>, Point<T>> closest_pair(vector<Point<T>> &v) {
  sort(v.begin(), v.end(), [&](const Point<T>&p, const Point<T>&q)
                           {return p.x!=q.x?p.x<q.x:p.y<q.y;});
  assert(v.size() > 1);
  Point<T> ans[2]; ans[0] = v[0], ans[1] = v[1];
  T opt = (ans[1]-ans[0]).norm2();
  dnc(0, v.size(), opt, ans[0], ans[1], v);
  return make_pair(ans[0], ans[1]);
}

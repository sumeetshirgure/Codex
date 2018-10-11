#pragma once
#include "Point.hh"

void dnc(size_t lx, size_t rx,
         Ptype &opt, Point &_p, Point &_q, vector<Point> &v) {
  if( rx - lx == 1 ) return;
  auto mid = (lx + rx)>>1;
  Ptype xmid = v[mid].x;
  dnc(lx, mid, opt, _p, _q, v);
  dnc(mid, rx, opt, _p, _q, v);
  inplace_merge(v.begin()+lx, v.begin()+mid, v.begin()+rx,
                [&](const Point&p, const Point&q) {
                  return p.y!=q.y?p.y<q.y:p.x<q.x;} );
  vector< Point > a;
  for(size_t i=lx; i<rx; i++)
    if( (v[i].x-xmid) * (v[i].x-xmid) <= opt )
      a.emplace_back(v[i]); // 2 * opt strip
  auto temp = opt;
  for(int i=0; i<(int)a.size(); i++)
    for(int j=i-1; j>=0 and (a[i].y-a[j].y)*(a[i].y-a[j].y) <= opt; j--)
      if( setMin(temp, (a[i]-a[j]).norm2()) ) _p=a[i], _q=a[j]; // O(1)
  opt = temp;
}

pair<Point, Point> closest_pair(vector<Point> &v) {
  sort(v.begin(), v.end(), [&](const Point&p, const Point&q)
                           {return p.x!=q.x?p.x<q.x:p.y<q.y;});
  assert(v.size() > 1);
  Point ans[2]; ans[0] = v[0], ans[1] = v[1];
  Ptype opt = (ans[1]-ans[0]).norm2();
  dnc(0, v.size(), opt, ans[0], ans[1], v);
  return make_pair(ans[0], ans[1]);
}

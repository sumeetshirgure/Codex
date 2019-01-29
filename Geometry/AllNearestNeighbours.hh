#pragma once
#include "../Header.hh"

template<typename T>
struct Point {
  int id; T x, y;
  Point() : x(0), y(0) {}
  Point(const T&_x, const T&_y) : x(_x), y(_y) {}
  inline T norm2() const& { return x*x+y*y; }
  inline auto norm() -> decltype(sqrt(norm2())) {return sqrt(norm2());}
};

/* Sums. */
template<typename T> Point<T> operator+(const Point<T>&p, const Point<T>&q)
{ return Point<T>(p.x+q.x, p.y+q.y); }
template<typename T> Point<T> operator-(const Point<T>&p, const Point<T>&q)
{ return Point<T>(p.x-q.x, p.y-q.y); }

/* Debugger. */
template<typename T> ostream& operator<<(ostream &out, const Point<T>&p)
{ return out << '[' << p.x << ' ' << p.y << ']'; }

template<typename T>
void dnc(int lx, int rx, vector<Point<T>> &v, vector<T> &dist) {
  if( rx - lx == 1 ) return;
  int mid = (lx + rx)>>1;
  T xmid = v[mid].x;
  dnc(lx, mid, v, dist); dnc(mid, rx, v, dist);
  auto cmpy = [&](const Point<T>&p, const Point<T>&q)->bool
  { return p.y!=q.y?p.y<q.y:p.x<q.x; };

  vector<Point<T>> L, R;
  for(int idx=lx; idx<mid; idx++) {
    auto dx = (v[idx].x-xmid);
    if( dx * dx < dist[v[idx].id] ) L.emplace_back(v[idx]);
  }
  for(int idx=mid; idx<rx; idx++) {
    auto dx = (v[idx].x-xmid);
    if( dx * dx < dist[v[idx].id] ) R.emplace_back(v[idx]);
  }

  auto relax = [&](int lo, int hi, const vector<Point<T>>&S) {
    for(int idx=lo, i=0; i<(int)S.size(); i++) {
      for(; idx<hi and v[idx].y < S[i].y; idx++);
      for(int jdx=idx; jdx<hi; jdx++) {
        auto del = v[jdx] - S[i];
        auto distance = del.norm2();
        smin(dist[v[jdx].id], distance);
        smin(dist[S[i].id], distance);
        if( dist[S[i].id] < del.y * del.y ) break;
      }
      for(int jdx=idx-1; jdx>=lo; jdx--) {
        auto del = v[jdx] - S[i];
        auto distance = del.norm2();
        smin(dist[v[jdx].id], distance);
        smin(dist[S[i].id], distance);
        if( dist[S[i].id] < del.y * del.y ) break;
      }
    }
  };

  relax(lx, mid, R); relax(mid, rx, L);
  inplace_merge(v.begin()+lx, v.begin()+mid, v.begin()+rx, cmpy);
}

template<typename T>
vector<T> nearest_neighbour_distances(vector<Point<T>> &v) {
  assert(v.size() > 1);
  vector<T> dist(v.size());
  for(int id=0; id<(int)v.size(); id++) v[id].id = id;
  dist[0] = (v[0]-v[1]).norm2();
  for(size_t i=1; i<v.size(); i++) dist[i] = (v[i]-v[0]).norm2();
  sort(v.begin(), v.end(), [&](const Point<T>&p, const Point<T>&q)
      {return p.x!=q.x?p.x<q.x:p.y<q.y;});
  dnc(0, v.size(), v, dist);
  return dist;
}

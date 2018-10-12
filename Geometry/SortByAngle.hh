#pragma once
#include "Point.hh"

/* Sorts by angles around origin. */
/* Equivalent to sorting by Point<T>::arg(), more or less. */
template<typename T>
void sort_by_angle(vector< Point<T> > &vec, const Point<T> &orig=Point<T>()) {
  auto it = partition(vec.begin(), vec.end(),
      [&](const auto&point){return point==orig;});
  auto mid = partition(it, vec.end(), [&](const Point<T>&p){
      return p.y != orig.y ? p.y < orig.y : p.x < orig.x; });
  auto angle_cmp = [&](const Point<T>&p, const Point<T>&q) {
    auto ccw = (p - orig) * (q - orig); 
    if( ccw != 0 ) return ccw > 0;
    return p.y != q.y ? p.y < q.y : p.x < q.x; };
  sort(it, mid, angle_cmp); sort(mid, vec.end(), angle_cmp);
}

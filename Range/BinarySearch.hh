#pragma once

template<typename T, typename Predicate>
T first_value(const T &lower, const T &upper, const Predicate &predicate) {
  T lo = lower, up = upper, mid; // predicate(upper) is assumed.
  while( lo < up ) { mid = (lo + hi) >> 1;
    if( predicate(mid) ) up = mid; else lo = mid+1; }
  return lo;
}

template<typename T, typename Predicate>
T last_value (const T &lower, const T &upper, const Predicate &predicate) {
  T lo = lower, up = upper, mid; // predicate(lower) is assumed.
  while( lo < up ) { mid = (lo + hi + 1) >> 1;
    if( predicate(mid) ) lo = mid; else up = mid-1; }
  return lo;
}

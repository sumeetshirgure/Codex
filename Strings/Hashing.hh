#pragma once

template< typename Ring > struct RKHash {
  int n;
  vector< Ring > h, p;
  RKHash (string const &s, Ring const&x) : n(s.length()), h(n+1), p(n+1) {
    h[0] = Ring::add_id(), p[0] = Ring::mul_id();
    for(int i=0; i<n; i++) h[i+1] = h[i] * x + s[i], p[i+1] = p[i] * x;
  };
  Ring interval_hash(int const&l, int const&r) // hash for [l, r)
  { return h[r] - h[l] * p[r-l]; }
};

template< typename Ring > vector< Ring >
rolling_hashes(string const&s, int len, Ring const&x) {
  int n = s.length();
  if( n < len ) return {};
  Ring h = Ring::add_id(), p = Ring::mul_id();
  for(int i=0; i<len; i++) h = h * x + s[i], p = p * x;
  vector< Ring > ret; ret.reserve(n - len + 1);
  ret.emplace_back(h);
  for(int i=len, j=0; i<n; i++, j++)
    ret.emplace_back(h = h * x + s[i] - p * s[j]);
  return ret;
}

struct R { /* Use only if necessary. */
  using T = int;
  T const static M = 1000000009;
  T x;
  R (T const&v=0) : x(v) { }
  T value() const { return x; }
  R operator+(R const&r) { T v =  x + r.x; if(v >= M) v -= M; return v; }
  R operator*(R const&r) { return (x * 1ll * r.x) % M; }
  R operator-(R const&r) { T v =  x - r.x; if(v <  0) v += M; return v; }
  bool operator==(R const&r) const { return x == r.x; }
  bool operator< (R const&r) const { return x <  r.x; }
  static const R add_id() { return R(0); }
  static const R mul_id() { return R(1); }
};

using ull = unsigned long long ;
struct H {
  ull x; H(ull x=0) : x(x) {}
#define OP(O,A,B) H operator O(H const&o)                               \
  { ull r = x; asm (A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B); return r; }
  OP(+,,"d"(o.x)) OP(*,"mul %1\n", "r"(o.x) : "rdx")
  H operator-(H const&o) { return *this + ~o.x; }
  inline ull value() const { return x + !~x; }
  bool operator==(H const&o) const { return value() == o.value(); }
  bool operator< (H const&o) const { return value() <  o.value(); }
  static const H add_id() { return 0; }
  static const H mul_id() { return 1; }
};

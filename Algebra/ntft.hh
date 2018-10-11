#pragma once
#include "../Header.hh"

namespace ntft {

  bool is_prime(ll _k, int _p) {
    ll x = 1 + (_k << _p);
    for(ll y=2; y*y<=x; y++)
      if( x % y == 0 ) return false;
    return true;
  }

  bool is_generator(ll _gen, ll _k, int _p) {
    ll _mod = 1 + (_k << _p);
    unordered_set<ll> H;
    for(ll x=_gen; H.find(x) == H.end(); x = (x*_gen)%_mod)
      H.emplace(x);
    return (int)H.size() == (1 << _p);
  }

  ll modular_inverse(ll x, ll _mod) {
    ll y = 1;
    for(int n=_mod-2; n>0; n>>=1, x = (x*x)%_mod)
      if(n & 1) y = (y*x) % _mod;
    return y;
  }

  int bit_reverse(int x, int lg) {
    int y = 0;
    for(int j=0, b=1, c=1<<lg; j<lg; j++, b<<=1) {
      c>>=1;
      if( x & b ) y |= c;
    }
    return y;
  }

  const ll k = 7;
  const int p = 20, L = 1<<p;
  const ll mod = 1 + k * L;

  const ll gen = 5, genInv = modular_inverse(gen, mod);

  void inplace_ntft(vector<ll> &a, bool invert=false) {
    size_t n = a.size(), lg = __builtin_ctz(n);

    for(size_t i=0; i<n; i++) {
      size_t j = bit_reverse(i, lg);
      if( j < i ) swap(a[j], a[i]);
    }

    for(size_t len=2, hfl=1; len<=n; len<<=1, hfl<<=1) {
      ll w = invert ? genInv : gen;
      for(ll temp=len; temp<L; temp<<=1)
        w = (w * w) % mod;
      for(size_t j=0; j<n; j+=len) {
        ll w0 = 1;
        for(size_t i=0; i<hfl; i++, w0=(w0*w)%mod) {
          ll x = a[j+i], y = (w0 * a[j+i+hfl]) % mod;
          ll p = x+y, q = x-y;
          if( p >= mod ) p -= mod;
          if( q < 0 ) q += mod;
          a[j+i] = p, a[j+i+hfl] = q;
        }
      }
    }

    if( invert ) {
      ll den = modular_inverse(n, mod);
      for(size_t i=0; i<n; i++)
        a[i] = (a[i] * den) % mod;
    }
  }

  vector<ll> multiply(const vector<ll> &_a, const vector<ll> &_b) {
    size_t n = 1, lg = 0;
    for(; n < _a.size() + _b.size(); n<<=1, lg++);
    vector<ll> a(n, 0), b(n, 0);
    copy(_a.begin(), _a.end(), a.begin());
    copy(_b.begin(), _b.end(), b.begin());
    inplace_ntft(a); inplace_ntft(b);
    for(size_t i=0; i<n; i++)
      a[i] = (a[i] * b[i]) % mod;
    inplace_ntft(a, true);
    a.resize(_a.size()+_b.size());
    return a;
  }

};

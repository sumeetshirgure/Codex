#pragma once
#include "../Header.hh"

namespace ntft {

  bool is_prime(ll _k, int _p) {
    ll x = 1 + (_k << _p);
    for(ll y=2; y*y<=x; y++)
      if( x % y == 0 ) return false;
    return true;
  }

  ll exponentiate(ll x, ll n, ll _mod) {
    ll y = 1;
    for(; n>0; n>>=1, x = (x*x)%_mod)
      if(n & 1) y = (y*x) % _mod;
    return y;
  }

  bool is_generator(ll _gen, ll _k, int _p) {
    ll _mod = 1+(_k<<_p);
    bool p_2 = exponentiate(_gen, (_mod-1)/ 2, _mod) != 1;
    bool p_k = exponentiate(_gen, (_mod-1)/_k, _mod) != 1;
    return p_2 and not p_k; // Has order exactly 2^_k.
  }

  inline ll modular_inverse(ll x, ll _mod)
  { return exponentiate(x, _mod-2, _mod); }

  int bit_reverse(int x, int lg) {
    int y = 0;
    for(int j=0, b=1, c=(1<<(lg-1)); j<lg; j++, b<<=1, c>>=1)
      if( x & b ) y |= c;
    return y;
  }

  const ll k = 7;
  const int p = 20, L = 1<<p;
  const ll mod = 1 + k * L;

  const ll gen = 5, genInv = modular_inverse(gen, mod);

  void inplace_ntft(vector<ll> &a, bool invert=false) {
    size_t n = a.size(), lg = __builtin_ctz(n);
    assert((n>>lg)==1);

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

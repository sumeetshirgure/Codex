#pragma once
#include "../Header.hh"

namespace Arithmetic {

  /* Modular exponentiation. */
  ll modular_exponentiation(ll x, ll p, ll mod) {
    // if( mod <= 1 ) return 0;
    // if( x >= mod or x < 0) x = (x % mod + mod) % mod;
    // if( p >= mod or p < 0) p = (p % phi(mod) + phi(mod)) % phi(mod);
    ll y = 1;
    for(; p>0; p>>=1, x = (x*x)%mod) if( p & 1 ) y = (y*x)%mod;
    return y;
  }

  /* Modular inverse. */
  bool modular_inverse(ll x, ll mod, ll &ans) {
    // return modular_exponentiation(x, phi(mod)-1, mod);
    ll temp;
    if( extended_euclidean(x, mod, ans, temp) != 1 ) return false;
    if( ans < 0 or ans >= mod ) ans = (ans % mod + mod) % mod;
    return true;
  }

  /* Solve equation of the form ax%mod == b%mod. */
  tuple<ll, ll, ll> modular_linear_equation_solver(ll a, ll b, ll mod) {
    ll x, y, g = extended_euclidean(a, mod, x, y);
    if( g == 0 or mod == 0 ) return {-1,-1,g};
    if( b % g ) return {-1,0,g};
    ll p = ((b / g) * x) % mod, q = mod / g;
    if( p < 0 ) p += mod;
    if( q < 0 ) q += mod;
    return {p, q, g}; // All solutions : {(p+i*q)%mod, i in [0,g)}
  }

  /* Chinese remainder theorem. */
  ll garner_restore(int n, ll residues[], ll moduli[]) {
    ll inv[n][n];
    for(int i=0; i<n; i++)
      for(int j=0; j<i; j++)
        assert(modular_inverse(moduli[j], moduli[i], inv[j][i]));
    ll x[n], ans = 0, cf = 1;
    for(int i=0; i<n; i++) {
      x[i] = residues[i];
      for(int j=0; j<i; j++) {
        x[i] = (inv[j][i] * (x[i]-x[j])) % moduli[i];
        if( x[i] < 0 ) x[i] += moduli[i];
      }
      ans = (ans + x[i] * cf), cf *= moduli[i];
    }
    return ans;
  }

};

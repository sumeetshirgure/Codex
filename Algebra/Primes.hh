#pragma once
#include "../Header.hh"

namespace Arithmetic {

  /* Factorisation and Euler's totient function. */
  int factorise(int n, vector<pair<int,int>> &f) {
    int phi = n;
    for(int i=2; i*i <= n; i++) if( n % i == 0 ) {
      f.emplace_back(i, 0);
      phi -= phi / i;
      while( n % i == 0 ) f.back().second++, n /= i;
    }
    if( n > 1 ) f.emplace_back(n, 1), phi -= phi / n;
    return phi;
  }

  /* Linearithmic sieve, find all divisors for all n. */
  void list_divisors(int n, vector<int> divisors[]) {
    for(int p=2; p<=n; p++) // if divisors[p].empty() : p is prime;
      for(int i=p; i<=n; i+=p) divisors[i].emplace_back(p);
  }

  /* Linear sieve. Find smallest prime divisors for all n. */
  void linear_sieve(int n, int spdf[], vector<int> &primes) {
    fill(spdf, spdf+1+n, 0);
    for(int p=2; p<=n; p++) {
      if( spdf[p] == 0 ) spdf[p] = p, primes.emplace_back(p);
      for(auto &prime: primes) {
        if( prime > spdf[p] or prime * p > n ) break;
        spdf[ prime * p ] = prime;
      }
    }
  }

  /* Precompute phi, given spdf. */
  void precompute_phi(int n, int spdf[], int f[]) {
    for(int i=2; i<=n; i++) {
      int p = spdf[i];
      if( p == i ) f[i] = p - 1;
      else if( spdf[i / p] != p ) f[i] = f[i / p] * (p - 1);
      else f[i] = f[i / p] * p;
    }
  }

  /* Primitive root modulo prime. */
  ll primitive_root(ll prime) {
    vector<pair<int,int>> f;
    ll phi = prime - 1;
    factorise(phi, f);
    ll gen = 2;
    for(; gen<prime; gen++) {
      bool is_generator = true;
      for(auto &factor: f)
        if( modular_exponentiation(gen, phi/factor.first, prime) == 1 )
        { is_generator = false; break; }
      if( is_generator ) return gen;
    }
    return prime;
  }

};

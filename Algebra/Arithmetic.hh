#pragma once
#include "../Header.hh"

namespace Arithmetic {

  ll extended_euclidean(ll a, ll b, ll &x, ll &y) {
    ll xx, yy, q, t; x = yy = 1, xx = y = 0;
    while( b != 0 ) {
      q = a / b, t = b, b = a % b, a = t;
      t = xx, xx = x - q * xx, x = t;
      t = yy, yy = y - q * yy, y = t;
    }
    return a;
  }

  /* Linear Diophantine equation solver. */
  bool lde_solver(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
    g = extended_euclidean(a, b, x, y);
    if( c % g != 0 ) return false;
    x *= c / g, y *= c / g;
    return true;
  }

  bool non_negative_lde(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
    if( not lde_solver(a, b, c, x, y, g) ) return false;
    if( x < 0 or y < 0 ) {
      ll dx = b / g, dy = a / g, steps;
      if( x < 0 ) steps = (-x + dx - 1) / dx;
      if( y < 0 ) steps = - (-y + dy - 1) / dy;
      x += steps * dx, y -= steps * dy;
      if( x < 0 or y < 0 ) return false;
    }
    return true;
  }

};

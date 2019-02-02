#pragma once
#include "../Header.hh"

template<typename Sequence> struct SuffixArray {
  int const n;
  vector< vector<int> > p;
  using Bucket = pair<pair<int, int>, int>;
  vector< Bucket > m;
  vector<int> sfx, lcpa;

  int lcp(int i, int j) {
    if( i == j ) return n - i;
    int len = 0;
    for(int k=p.size()-1, b=(1<<k); b>0 and i<n and j<n; k--, b>>=1)
      if( p[k][i] == p[k][j] ) i += b, j += b, len += b;
    return len;
  }

  SuffixArray(Sequence const&s) :
  n(std::end(s) - std::begin(s)), p(1, vector<int>(n, 0)), m(n), sfx(n), lcpa(n) {
    for(int i=0; i<n; i++) p[0][i] = (int)(s[i]);
    for(int j=1, b=1; b<n; b<<=1, j++) {
      p.emplace_back(vector<int>(n, 0));
      for(int i=0; i<n; i++) m[i] = {{p[j-1][i], i+b<n ? p[j-1][i+b] : -1}, i};
      sort(all(m));
      for(int l=0,r=0; l<n; l=r)
        for(; r<n and m[r].ff == m[l].ff; r++) p[j][ m[r].ss ] = l;
    }
    iota(all(sfx), 0);
    auto&ranks = p.back();
    sort(all(sfx), [&ranks](int const&u, int const&v)
    { return ranks[u] != ranks[v] ? ranks[u] < ranks[v] : u < v; });
    for(int i=1; i<n; i++) lcpa[i] = lcp(sfx[i-1], sfx[i]);
    m.clear();
  }

  int const& operator[](size_t const&i) const { return sfx[i]; }
};

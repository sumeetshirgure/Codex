#include "../Header.hh"

/* Disjoint set union-find structure.
   Use path compression and rank comparison. */
template<typename T>
struct DSU {
  vector<int> par, rank;
  vector<T> data;

  DSU(const size_t &_n) {
    par.resize(_n), rank.resize(_n);
    data.resize(_n);
    iota(par.begin(), par.end(), 0);
    fill(rank.begin(), rank.end(), 0);
  }

  inline int find(int x) {
    int y, t;
    for(y = x; par[y] != y; y = par[y]);
    for(; x != y; t = par[x], par[x] = y, x = t);
    return y; // return par[x] == x ? x : par[x] = find(par[x]);
  }

  bool unite(int u, int v) {
    u = find(u), v = find(v);
    if( u == v ) return false;
    if( rank[v] > rank[u] ) swap(u, v);
    if( rank[u] == rank[v] ) rank[u]++;
    par[v] = u;
    data[u] = combine(data[u], data[v]);
    return true;
  }

  T& operator[](const size_t &index) {
    if( index >= par.size() )
      throw out_of_range("Out of range");
    return data.at( find( index ) );
  }

  inline void makeParent(int u) {
    par[u] = par[find(u)] = u;
  }
};


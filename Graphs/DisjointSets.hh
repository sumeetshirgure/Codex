#pragma once
#include "../Header.hh"

/* Disjoint set union-find structure. Uses path compression. */
template<typename T>
struct DSU {
  vector<int> par, rank;
  vector<T> data;

  DSU(const size_t &_n) {
    par.resize(_n), rank.resize(_n);
    data.resize(_n);
    iota(par.begin(), par.end(), 0);
    fill(rank.begin(), rank.end(), 1);
  }

  int find(int x) {
    return par[x] == x ? x : par[x] = find(par[x]);
  }

  int unite(int u, int v) {
    u = find(u), v = find(v);
    if( u == v ) return u;
    int parent = u, child = v;
    if( rank[child] > rank[parent] ) swap(parent, child);
    if( rank[parent] == rank[child] ) rank[parent]++;
    par[child] = parent;
    data[parent] = combine(data[u], data[v]);
    return parent;
  }

  T& operator[](const size_t &index) {
    if( index >= par.size() )
      throw out_of_range("Out of range");
    return data.at( find( index ) );
  }

  inline void make_parent(int u) {
    int v = find(u);
    if( u == v ) return;
    par[u] = par[v] = u;
    swap(data[u], data[v]);
  }
};

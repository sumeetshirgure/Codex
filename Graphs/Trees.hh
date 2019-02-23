#pragma once
#include "../Header.hh"

int const N = 2e5 + 1, L = 32 - __builtin_clz(N);
vector< int > tree[N];
int n, st[N], en[N], inv[N], timer, anc[L][N];

void lca_dfs(int u, int parent) {
  st[u] = ++timer;
  inv[timer] = u;
  anc[0][u] = parent;
  for(int const&v: tree[u]) {
    if( v == parent ) continue;
    lca_dfs(v, u);
  }
  en[u] = timer;
}

void init_lca(int root) {
  timer = 0, st[0] = 0, en[0] = n, anc[0][0] = 0;
  lca_dfs(root, 0);
  for(int j=1; j<L; j++)
    for(int i=0; i<=n; i++)
      anc[j][i] = anc[j-1][ anc[j-1][i] ];
}

inline bool is_ancestor(int u, int v)
{ return st[u] <= st[v] and en[v] <= en[u]; }

int lca(int u, int v) {
  if( st[u] > st[v] ) swap(u, v);
  if( is_ancestor(u, v) ) return u;
  for(int j=L-1; j>=0; j--) {
    int w = anc[j][v];
    if( not is_ancestor(w, u) ) v = w;
  }
  return anc[0][v];
}

/* Heavy path decomposition. */
int ssz[N], meet[N];
void fssz(int u, int parent) {
  anc[0][u] = parent;
  auto&adj = tree[u];
  adj.erase(remove(all(adj), parent), adj.end());
  ssz[u] = 1;
  for(auto &v: adj) { fssz(v, u); ssz[u] += ssz[v]; }
  for(int i=1; i<(int)adj.size(); i++)
    if( ssz[ adj[i] ] > ssz[ adj[0] ] ) swap(adj[0], adj[i]);
}

void hld(int u, int lane) {
  auto&adj = tree[u];
  meet[u] = lane;
  st[u] = ++timer;
  for(auto &v: adj) hld(v, (v == adj[0] ? lane : v));
  en[u] = timer;
}

void init_hld(int root) {
  fssz(root, 0);
  timer = 0, st[0] = 0, en[0] = n, anc[0][0] = 0;
  hld(root, root);
  for(int j=1; j<L; j++)
    for(int i=0; i<=n; i++)
      anc[j][i] = anc[j-1][ anc[j-1][i] ];
}

vector< pair<int, int> > decompose_path(int u, int v) { // (st[u], st[v]]
  // assert( is_ancestor(u, v) );
  vector< pair<int, int> > ret;
  int x, y;
  for(x = v, y = meet[x]; not is_ancestor(y, u); x = anc[0][y], y = meet[x])
    ret.emplace_back(st[y], st[x]);
  if( st[u] < st[x] ) ret.emplace_back(st[u]+1, st[x]); // (st[u], st[x]] for edges
  return ret;
}

/* Centroid decomposition. */
int csz;
bool mark[N];

void probe(int u, int parent) {
  ssz[u] = 1;
  for(auto &v: tree[u]) {
    if( v == parent or mark[v] ) continue;
    probe(v, u), ssz[u] += ssz[v];
  }
}

int find_centroid(int u, int parent) {
  for(auto &v: tree[u])
    if( not (v == parent or mark[v]) and ssz[v] * 2 >= csz )
      return find_centroid(v, u);
  return u;
}

void decompose(int u) {
  probe(u, -1), csz = ssz[u];
  int centroid = find_centroid(u, -1);
  mark[ centroid ] = 1;
  for(auto &v: tree[ centroid ]) { if( mark[v] ) continue; /* Accumulate. */ }
  for(auto &v: tree[ centroid ]) if( not mark[v] ) decompose(v);
}

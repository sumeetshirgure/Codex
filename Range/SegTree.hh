#pragma once

template<typename Node, typename Query=Node, typename Update=Node>
struct SegTree {
  vector<Node> tree;

  int lo, hi, qlo, qhi;
  Update update;

  SegTree(int sz) : lo(0), hi(sz) { tree.resize(sz<<2); }
  SegTree(int lo, int hi) : lo(lo), hi(hi) { tree.resize((hi-lo)<<2); }

  inline void push(const int&x, const int &lx, const int &rx);
  inline void pull(const int&x, const int &lx, const int &rx);
  inline void mark(const int&x, const int &lx, const int &rx);

  inline Query get_query(const Node &node);
  inline Query combine(const Query &lq, const Query&rq);

  void tree_update(int x, int lx, int rx) {
    push(x, lx, rx);
    if( rx <= qlo || qhi <= lx ) return;
    if( qlo <= lx && rx <= qhi ) { mark(x, lx, rx); push(x, lx, rx); return; }
    int mid = (lx + rx) >> 1;
    tree_update(x + x, lx, mid), tree_update(x+1+x, mid, rx);
    pull(x, lx, rx);
  }

  Query tree_query(int x, int lx, int rx) {
    push(x, lx, rx);
    if( qlo <= lx && rx <= qhi ) return get_query(tree[x]);
    int mid = (lx + rx) >> 1;
    if( qhi <= mid ) return tree_query(x + x, lx, mid);
    if( qlo >= mid ) return tree_query(x+1+x, mid, rx);
    return combine(tree_query(x+x, lx, mid), tree_query(x+1+x, mid, rx));
  }

  void put(int u, int v, const Update&val)
  { update = val, qlo = u, qhi = v; tree_update(1, lo, hi); };

  Query get(int u, int v)
  { qlo = u, qhi = v; return tree_query(1, lo, hi); };
};

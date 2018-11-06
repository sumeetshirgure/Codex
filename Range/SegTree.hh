#pragma once

template<typename Node, typename Query=Node, typename Update=Node>
struct SegTree {
  vector<Node> tree;
  SegTree(int sz) : lo(0), hi(sz) { tree.resize(sz<<2); }
  SegTree(int lo, int hi) : lo(lo), hi(hi) { tree.resize((hi-lo)<<2); }

  int lo, hi, qlo, qhi;
  Update update;

  void push(const int&x, const int &lx, const int &rx);
  void pull(const int&x, const int &lx, const int &rx);
  void mark(const int&x, const int &lx, const int &rx);

  Query get_query(const Node &);
  Query combine(const Query &lq, const Query&rq);

  void tree_update(int x, int lx, int rx) {
    push(x, lx, rx);
    if( rx <= qlo || qhi <= lx ) return;
    if( qlo <= lx && rx <= qhi ) { mark(x, lx, rx); push(x, lx, rx); return; }
    int mid = (lx + rx) >> 1;
    tree_update(x + x, lx, mid); tree_update(x+1+x, mid, rx);
    pull(x, lx, rx);
  }
  Query tree_query(int x, int lx, int rx) {
    push(x, lx, rx);
    if( rx <= qlo || qhi <= lx ) return Query();
    if( qlo <= lx && rx <= qhi ) return get_query(tree[x]);
    int mid = (lx + rx)>>1;
    if( rx <= mid ) return tree_query(x + x, lx, mid);
    if( lx >= mid ) return tree_query(x+1+x, mid, rx);
    return combine(tree_query(x+x, lx, mid), tree_query(x+1+x, mid, rx));
  }
  void put(int u, int v, const Update&val) 
  { update = val, qlo = u, qhi = v; tree_update(1, lo, hi); };
  Query get(int u, int v) { qlo = u, qhi = v; return tree_query(1, lo, hi); };
};
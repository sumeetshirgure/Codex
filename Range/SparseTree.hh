#pragma once

struct SparseTree {
  struct Node {
    ll rs; Node *l, *r;
    Node(const ll&val=0): rs(val), l(nullptr), r(nullptr) { }
  };
  inline ll get_sum(Node *t) { return t == nullptr ? 0 : t->rs; }
  Node *root;
  ll lo, hi, _p, _q;
  SparseTree(const ll &sz):root(nullptr), lo(0), hi(sz) {}
  SparseTree(const ll &lo, const ll &hi):root(nullptr), lo(lo), hi(hi) {}
  /* Point update. */
  void update(Node *&t, ll lx, ll rx) {
    if( t == nullptr ) t = new Node();
    if( rx - lx == 1 ) { t->rs += _q; return; }
    ll mid = (lx + rx)>>1;
    if( _p < mid ) update(t->l, lx, mid); else update(t->r, mid, rx);
    t->rs = get_sum(t->l) + get_sum(t->r);
  }
  void update(ll pos, ll val) { _p = pos; _q = val; update(root, lo, hi); }
  /* Range sum query. */
  ll query(Node *t, ll lx, ll rx) {
    if( t == nullptr or rx <= _p or _q <= lx ) return 0;
    if( _p <= lx and rx <= _q ) return t->rs;
    ll mid = (lx + rx)>>1;
    return query(t->l, lx,  mid) + query(t->r, mid, rx);
  }
  ll query(ll lx, ll rx) { _p = lx, _q = rx; return query(root, lo, hi); }
};

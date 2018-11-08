#pragma once

struct PersistentTree {
  struct Node {
    ll rs; Node *l, *r;
    Node(const ll&val=0): rs(val), l(nullptr), r(nullptr) { }
  };
  inline ll get_sum(Node *t) { return t == nullptr ? 0 : t->rs; }
  ll lo, hi, _p, _q;
  PersistentTree(const ll &sz):lo(0), hi(sz) {}
  PersistentTree(const ll &lo, const ll &hi):lo(lo), hi(hi) {}
  /* Persistent point update. */
  Node* update(Node *&t, ll lx, ll rx) {
    if( _p < lx or _p >= rx ) return t;
    Node *ret;
    if( t == nullptr ) t = ret = new Node(); // *Fresh branch.
    else ret = new Node(*t);
    if( _p == lx and rx - lx == 1 ) { ret->rs += _q; return ret; }
    ll mid = (lx + rx)>>1;
    ret->l = update(t->l, lx, mid), ret->r = update(t->r, mid, rx);
    ret->rs = get_sum(ret->l) + get_sum(ret->r);
    return ret;
  }
  Node* put(Node *&version, ll pos, ll val) {
    _p = pos; _q = val;
    return update(version, lo, hi);
  }
  /* Range sum query. */
  ll query(Node *t, ll lx, ll rx) {
    if( t == nullptr or rx <= _p or _q <= lx ) return 0;
    if( _p <= lx and rx <= _q ) return t->rs;
    ll mid = (lx + rx)>>1;
    return query(t->l, lx,  mid) + query(t->r, mid, rx);
  }
  ll get(Node *version, ll lx, ll rx) {
    _p = lx, _q = rx;
    return query(version, lo, hi);
  }
};

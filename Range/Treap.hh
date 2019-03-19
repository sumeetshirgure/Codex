#pragma once
#include "../Header.hh"

uniform_int_distribution<int> prygen;
struct Treap {

  struct Node {
    int sz, pry;
    ll val, xs, sm;
    bool rev;
    Node *l, *r;
    Node(const int &v): sz(1), pry(prygen(rng)), val(v), xs(0), sm(v),
    rev(false), l(nullptr), r(nullptr) { }
  };

  Node *root = nullptr;

  inline static int getsz(Node *node) {return node == nullptr ? 0 : node->sz;}
  inline static ll  getsm(Node *node) {return node == nullptr ? 0 : node->sm;}

  inline void push(Node *&t) {
    if( t == nullptr ) return;
    if( t->rev ) {
      t->rev = false;
      swap(t->l, t->r);
      if( t->l != nullptr ) t->l->rev ^= true;
      if( t->r != nullptr ) t->r->rev ^= true;
    }
    if( t->xs != 0 ) {
      t->val += t->xs;
      t->sm += t->xs * getsz(t);
      if( t->l != nullptr ) t->l->xs += t->xs;
      if( t->r != nullptr ) t->r->xs += t->xs;
      t->xs = 0;
    }
  }

  inline void pull(Node *&t) {
    if( t == nullptr ) return;
    t->sz = getsz(t->l) + getsz(t->r) + 1;
    push(t->l), push(t->r);
    t->sm = getsm(t->l) + getsm(t->r) + t->val;
  }

  /* Split treap assuming initial offset of `ord'. */
  void split(const int &pos, int &ord, Node *t, Node *&l, Node *&r) {
    if( t == nullptr ) { l = r = nullptr; return; }
    push(t);
    int lsz = getsz(t->l);
    if( pos <= ord + lsz ) { split(pos, ord, t->l, l, t->l); r = t; }
    else { ord += 1 + lsz; split(pos, ord, t->r, t->r, r); l = t; }
    pull(t);
  }

  /* Join treaps. */
  void join(Node *&t, Node *lt, Node *rt) {
    if(lt==nullptr or rt==nullptr) {t=(lt == nullptr ? rt : lt); return;}
    push(lt); push(rt);
    if( lt->pry >= rt->pry ) { join(lt->r, lt->r, rt); t = lt; }
    else { join(rt->l, lt, rt->l); t = rt; }
    pull(t);
  }

  /* Insert element at position. */
  void insert(const int &pos, const int &val) {
    Node *t1 = nullptr, *t2 = nullptr;
    int ord = 0;
    split(pos, ord, root, t1, t2); 
    Node *x = new Node(val);
    join(root, t1, x); join(root, root, t2);
  }

  /* Reverse subrange. */
  void reverse(int lx, int rx) {
    Node *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
    int ord = 0; // Store offset.
    split(lx, ord, root, t1, t2); split(rx, ord, t2, t2, t3);
    if( t2 != nullptr ) t2->rev ^= true; // Reverse.
    join(root, t1, t2); join(root, root, t3);
  }

  /* Range sum. */
  ll range_sum(int lx, int rx) {
    Node *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
    int ord = 0;
    split(lx, ord, root, t1, t2); split(rx, ord, t2, t2, t3);
    ll ans = getsm(t2);
    join(root, t1, t2); join(root, root, t3);
    return ans;
  }

  /* Range compressable update. */
  void range_add(int v, int lx, int rx) {
    Node *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
    int ord = 0;
    split(lx, ord, root, t1, t2); split(rx, ord, t2, t2, t3);
    if( t2 != nullptr ) t2->xs += v;
    join(root, t1, t2); join(root, root, t3);
  }

  /* Rotate subrange by k. Analogous to std::rotate. */
  void rotate(int lx, int rx, int k) {
    if( k >= rx-lx ) k %= (rx - lx); 
    if( k == 0) return;
    Node *t1 = nullptr, *t2 = nullptr, *t3 = nullptr, *t4 = nullptr;
    int ord = 0;
    split(lx, ord, root, t1, t2);
    split(lx+k, ord, t2, t2, t3);
    split(rx, ord, t3, t3, t4);
    join(root, t1, t3); join(root, root, t2); join(root, root, t4);
  }

  /* Inorder traversal. */
  void dfs(Node *t, vll &v) {
    if( t == nullptr ) return;
    push(t);
    dfs(t->l, v);
    v.emplace_back(t->val);
    dfs(t->r, v);
  }
  vll linearise() { vll ret; dfs(root, ret); return ret; }

};

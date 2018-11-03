#pragma once
#include "../Header.hh"
#include "Point.hh"

uniform_int_distribution<int> prygen;
template<typename T> struct Dynamic_Hull {

  struct Node {
    int pry;
    Point<T> u, v; // u < v
    Node *l, *r;
    Node(const Point<T> &u, const Point<T>&v):
      pry(prygen(rng)), u(u), v(v), l(nullptr), r(nullptr) { }
  };

  Point<T> first, last;
  Node *root = nullptr;
  Dynamic_Hull(const Point<T> &p, const Point<T> &q) {
    if( q < p ) first = q, last = p; else first = p, last = q;
    root = new Node(first, last);
  }

  /* Split treap using given predicate.
   * Assumes all false values occur before true values. */
  template<typename Predicate>
  void split(const Predicate &pred, Point<T>&p, Node *t, Node *&l, Node *&r) {
    if( t == nullptr ) { l = r = nullptr; return; }
    if( pred(*t) ) p = t->u, split(pred, p, t->l, l, t->l), r = t;
    else p = t->v, split(pred, p, t->r, t->r, r), l = t;
  }

  /* Join treaps. */
  void join(Node *&t, Node *lt, Node *rt) {
    if(lt==nullptr or rt==nullptr) {t=(lt == nullptr ? rt : lt); return;}
    if( lt->pry >= rt->pry ) join(lt->r, lt->r, rt), t = lt;
    else join(rt->l, lt, rt->l), t = rt;
  }

  /* Deallocate treap. */
  void erase(Node *&t) {
    if(t==nullptr) return;
    erase(t->l), erase(t->r);
    delete t; t = nullptr;
  }

  /* "Peel off" some rightmost segments of the left chain. */
  inline void peel_left (Node *&chain, Point<T>&tangent, const Point<T> &p) {
    Node *inside=nullptr, *outside=nullptr;
    auto lcmp = [&](const Node&node)->bool
    { return (node.v-node.u)*(p-node.u) <= 0; };
    split(lcmp, tangent, chain, inside, outside);
    erase(outside);
    join(chain, inside, new Node(tangent, p));
  }

  /* "Peel off" some leftmost segments of the right chain. */
  inline void peel_right(Node *&chain, Point<T>&tangent, const Point<T> &p) {
    Node *outside=nullptr, *inside=nullptr;
    auto rcmp = [&](const Node&node)->bool
    { return (node.v-node.u)*(p-node.u) > 0; };
    split(rcmp, tangent, chain, outside, inside);
    erase(outside);
    join(chain, new Node(p, tangent), inside);
  }

  /* Inserts point into the hull. Returns true if p is outside the hull. */
  bool insert_point(const Point<T> &p) {
    if( last < p ) { peel_left(root, last, p), last = p; return true; }
    if( p < first ) { peel_right(root, first, p), first = p; return true; }

    Node *left_chain=nullptr, *segment=nullptr, *right_chain=nullptr;
    Point<T> left_tangent, right_tangent;
    split([&](const Node &node)->bool { return p < node.u; },
        right_tangent, root, left_chain, right_chain);
    split([&](const Node &node)->bool { return not (node.v < p); },
        left_tangent, left_chain, left_chain, segment);

    bool inside = ((segment->v-segment->u)*(p-segment->u) >= 0);
    if( inside ) {
      join(left_chain, left_chain, segment);
      join(root, left_chain, right_chain);
      return false;
    }
    erase(segment);
    peel_left(left_chain, left_tangent, p);
    peel_right(right_chain, right_tangent, p);
    join(root, left_chain, right_chain);
    return true;
  }

  /* Inorder traversal. */
  void print(Node *t) {
    if( t == nullptr ) return;
    print(t->l); cerr << t->u << ' '; print(t->r);
  }
  void print() { print(root); cerr << last << endl; }
};

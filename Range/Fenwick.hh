#pragma once

template<typename T>
struct Fenwick {
  vector<T> tree;
  Fenwick(const size_t &n=0, const T&val=T()) { tree.resize(n, val); };
  T get(int pos) {
    if(pos >= (int)tree.size()) throw out_of_range("Index out of range.");
    T ret = 0;
    for(; pos >= 0; pos=(pos&(pos+1))-1) ret += tree[pos];
    return ret;
  }
  void put(int pos, const T &val) {
    if(pos < 0) throw out_of_range("Index out of range.");
    for(; pos < (int)tree.size(); pos|=(pos+1)) tree[pos] += val;
  }
  // Return first index with partial sum >= acc, or n if no such index.
  int lower_bound(const T &acc) { return (int)tree.size(); }
};

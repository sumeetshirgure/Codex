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
  // Return first index with partial sum > acc, n if acc exceeds total sum.
  int upper_bound(T acc) {
    int idx = 0, x = (1<<30);
    for(; x>0; x>>=1) {
      if( idx+x-1 >= (int)tree.size() ) continue;
      if( acc >= tree[idx+x-1] ) acc -= tree[idx+x-1], idx += x;
    }
    return idx;
  }
};

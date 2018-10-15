#pragma once
#include "../Header.hh"

/* Knuth-Morris-Pratt's pi function. */
template<typename T, typename... Args,
         template<typename, typename...> typename Sequence>
vector<int> kmp_pi(const Sequence<T, Args...>&seq) {
  int n = std::end(seq) - std::begin(seq);
  vector<int> pi(1+n);
  pi[0] = pi[1] = 0;
  for(int j=pi[1], i=2; i<=n; i++) {
    while( j > 0 and seq[j] != seq[i-1] ) j = pi[j];
    if( seq[j] == seq[i-1] ) j++;
    pi[i] = j;
  }
  return pi;
}

/* String matcher DFA. */
template<typename State>
vector<State> matcher_aut(const string &alphabet, const string&seq) {
  auto pi = kmp_pi(seq);
  vector<State> dfa(pi.size());
  for(int i=0; i < (int)dfa.size(); i++) {
    for(const auto &c:alphabet)
      if( i < (int)seq.size() and c == seq[i] ) dfa[i][c] = i+1;
      else dfa[i][c] = dfa[pi[i]][c];
  }
  return dfa;
}

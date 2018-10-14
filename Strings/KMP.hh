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

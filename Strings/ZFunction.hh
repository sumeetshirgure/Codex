#pragma once
#include "../Header.hh"

/* Z function. */
template<typename T, typename... Args,
         template<typename, typename...> typename Sequence>
vector<int> z_function(const Sequence<T, Args...>&seq) {
  int n = std::end(seq) - std::begin(seq);
  vector<int> z(n); z[0] = n;
  for(int i=1, l=0, r=0; i<n; i++) {
    if( i <= r ) z[i] = min(z[i-l], r-i+1);
    while(i+z[i]<n and seq[z[i]] == seq[i+z[i]]) ++z[i];
    if( i+z[i]-1 > r ) l=i, r=i+z[i]-1;
  }
  return z;
}


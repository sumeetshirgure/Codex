#include "../Header.hh"

/* Manacher's algorithm for finding all palindromic radii. */
template<typename T, typename... Args,
         template<typename, typename...> typename Sequence>
vector<int> manacher(const Sequence<T, Args...>&seq, const T& stuffing=-1){
  int n = std::end(seq) - std::begin(seq); // length
  T t[n+n+1]; // stuffed sequence
  fill(t, t + n + n + 1, stuffing);
  for(int i=0;i<n;i++)
    t[i+i+1] = seq[i];
  vector<int> rad(2*n+1, 0);
  for(int x = 0, i = 1; i < 2*n; i++){
    auto &r = rad[i];
    if( x+rad[x]-i >= 0) r = min(x+rad[x]-i, rad[x+x-i]);
    while(i-r-1>=0 and i+r+1<=2*n and t[i-r-1]==t[i+r+1]) r++;
    if(i+r >= x+rad[x]) x=i;
  } // radii w.r.t stuffed sequence t
  for(auto &r:rad) r /= 2;
  return rad;
}

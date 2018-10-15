#pragma once
#include "../Header.hh"

namespace SuffixArray {

  const int L = 17, N = (1<<L);
  int lvl, rank[L][N], last[N], sid[N], cnt[N], n, sfx[N], lcpa[N];
  char s[N];
  using Bucket = pair< pair<int,int>, int >;
  Bucket buckets[N], temp_buckets[N];
  const int SIGMA = 256;

  int lcp(int x, int y) {
    int len = 0, xlim = last[x], ylim = last[y];
    for(int j=lvl, b=1<<j; j>=0; j--, b>>=1) {
      if( x+b<=xlim and y+b<=ylim and rank[j][x] == rank[j][y] )
        x += b, y += b, len+=b;
    }
    return len;
  }

  inline void sort_buckets(Bucket arr[]=buckets, Bucket tmp[]=temp_buckets) {
    fill(cnt, cnt+n+1, 0);
    for(int i=1; i<n; i++) cnt[ arr[i].ff.ss ]++;
    for(int i=1; i<=n; i++) cnt[i] += cnt[i-1];
    for(int i=n-1; i>=1; i--) tmp[cnt[arr[i].ff.ss]--] = arr[i];
    fill(cnt, cnt+n+1, 0);
    for(int i=1; i<n; i++) cnt[ tmp[i].ff.ff ]++;
    for(int i=1; i<=n; i++) cnt[i] += cnt[i-1];
    for(int i=n-1; i>=1; i--) arr[cnt[tmp[i].ff.ff]--] = tmp[i];
  }

  void build_array(const vector<string>&D) {
    s[0] = '$'; n = 1;
    for(int idx=0; idx < (int)D.size(); idx++) {
      const auto& str = D[idx];
      for(int i=0; i<(int)str.length(); i++) s[n+i] = str[i];
      fill(last+n, last+n+str.length(), n+str.length());
      fill(sid+n, sid+n+str.length(), idx);
      n += str.length();
    }
    fill(cnt, cnt+SIGMA, 0);
    for(int i=1; i<n; i++) cnt[(int)s[i]]++;
    for(int acc=1, i=0; i<SIGMA; i++)
      swap(acc, cnt[i]), acc += cnt[i];
    for(int i=1; i<n; i++) rank[0][i] = cnt[(int)s[i]];
    lvl = 0;
    for(int j=1, b=(1<<lvl); b<n; lvl++, j++, b<<=1) {
      for(int i=1; i<n; i++)
        buckets[i] = {{rank[lvl][i],(i+b<last[i]?rank[lvl][i+b]:0)},i};
      sort_buckets(); // sort(buckets+1, buckets+n);
      for(int l=1, r=1; l<n; l=r)
        for(; r<n and buckets[r].ff == buckets[l].ff; r++)
          rank[j][ buckets[r].ss ] = l;
    }
    fill(cnt, cnt+1+n, 0);
    for(int i=1; i<n; i++) cnt[ rank[lvl][i] ]++;
    for(int i=1; i<=n; i++) cnt[i] += cnt[i-1];
    for(int i=n-1; i>=1; i--) sfx[ cnt[rank[lvl][i]]-- ] = i;
    for(int i=1; i+1<n; i++) lcpa[i] = lcp(sfx[i], sfx[i+1]);
  }

  void sort_all_substrings(const vector<string> &v) {
    build_array(v);
    for(int r=1; r<n; r++) {
      int pos = sfx[r];
      cout << pos << "\t:\t";
      for(int j=pos; j<last[pos]; j++) cerr << s[j];
      cerr << endl;
    }
  }

};

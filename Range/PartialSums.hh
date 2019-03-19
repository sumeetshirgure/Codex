#pragma once

const int D0 = 4, D1 = 2, D2 = 7;
template<typename T> void half_plane_partial_sums(T a[D0][D1][D2]) {
  int d[3] = {1,0,0};
  for(int dim=0; dim<3; d[dim++]=0) {
    d[dim]=1;
    for(int i0=0, d0=i0+d[0]; d0<D0; i0++, d0++)
      for(int i1=0, d1=i1+d[1]; d1<D1; i1++, d1++)
        for(int i2=0, d2=i2+d[2]; d2<D2; i2++, d2++)
          a[d0][d1][d2] += a[i0][i1][i2];
  }
  // Calculate subspace sums using inclusion - exclusion O(2^dims).
}

template<typename T> void hypercube_partial_sums(int k, T a[]) {
  for(int j=0, b=1; j<k; j++, b<<=1)
    for(int i=0; i<(1<<k); i++) if(i&b) a[i^b] += a[i];
  // a[i] now stores sigma{(j&i)==i}(a[j]). Use symmetry for (j|i)==i.
}

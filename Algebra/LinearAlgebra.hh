#pragma once
#include "../Header.hh"


template<typename T=int> struct Matrix {
  int n, m;
  vector< vector<T> > mat;
  Matrix(int const&_n, int const&_m) :
    n(_n), m(_m), mat(vector< vector<T> >(n, vector<T>(m, T()))) { };

  void operator+=(Matrix<T> const&b) {
    if( n != b.n or m != b.m ) throw invalid_argument("+dimension mismatch");
    for(auto it=mat.begin(), jt=b.mat.begin(); it!=mat.end(); it++, jt++)
      for(auto p=it->begin(), q=jt->begin(); p!=it->end(); p++, q++) (*p) = (*p) + (*q);
  }
  Matrix<T> operator+(Matrix<T> const&b) { auto ret = *this; ret += b; return ret; }

  Matrix<T> operator*(Matrix<T> const&b) const {
    if( m != b.n ) throw invalid_argument("*dimension mismatch");
    Matrix<T> ret(n, b.m);
    for(int i=0; i<n; i++)
      for(int j=0; j<b.m; j++) {
        T temp = T();
        for(int k=0; k<m; k++) temp += (mat[i][k] * b.mat[k][j]);
        ret.mat[i][j] = temp;
      }
    return ret;
  }
  inline void operator*=(Matrix<T> const&b) { mat = Matrix<T>(*this * b).mat; }

  vector<T>& operator[] (int const&row) { return mat[row]; }
  vector<T>const& operator[] (int const&row) const { return mat[row]; }
};

template<typename T> string to_string(Matrix<T> const&mat) {
  string ret = "\n";
  for(auto &row: mat.mat) ret += to_string(row), ret += "\n";
  return ret;
}

template<typename T> Matrix<T> matexp(Matrix<T> const&m, int ex, Matrix<T> const&ID) {
  auto ret = ID, sq = m;
  for(; ex>0; ex>>=1, sq *= sq)
    if(ex&1) ret *= sq;
  return ret;
}

/* Gaussian-Jordan elimination over a field. */
template<typename T> void GaussJordan(Matrix<T> a, Matrix<T>&b) {
  assert(b.n == a.n);
  int n = a.n, m = a.m;
  int i, j ,k;
  for(k=0; k<n; k++) { //
    for(j=k, i=k+1; i<n; i++) if( abs(a[i][k]) > abs(a[j][k]) ) j = i;
    swap(a[j], a[k]), swap(b[j], b[k]);
    T piv = a[k][k];
    if( piv == 0 ) return; // Singular.
    for(j=0; j<m; j++) a[k][j] = (a[k][j] / piv);
    for(j=0; j<b.m; j++) b[k][j] = (b[k][j] / piv);
    for(i=0; i<n; i++) {
      if( i == k ) continue;
      piv = a[i][k];
      for(j=0; j<m; j++) a[i][j] -= piv * a[k][j];
      for(j=0; j<b.m; j++) b[i][j] -= piv * b[k][j];
    }
  }
}

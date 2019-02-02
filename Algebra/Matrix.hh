#pragma once
#include "../Header.hh"

template<typename T=int> struct Matrix {
  size_t const n, m;
  vector< vector<T> > mat;
  Matrix(size_t const&_n, size_t const&_m) :
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
    for(size_t i=0; i<n; i++)
      for(size_t j=0; j<b.m; j++) {
        T temp = T();
        for(size_t k=0; k<m; k++) temp += (mat[i][k] * b.mat[k][j]);
        ret.mat[i][j] = temp;
      }
    return ret;
  }
  inline void operator*=(Matrix<T> const&b) { mat = Matrix<T>(*this * b).mat; }

  vector<T>& operator[] (size_t const&row) { return mat[row]; }
  vector<T>const& operator[] (size_t const&row) const { return mat[row]; }
};

template<typename T> string to_string(Matrix<T> const&mat) { return to_string(mat.mat); }

template<typename T> Matrix<T> matexp(Matrix<T> const&m, size_t ex, Matrix<T> const&ID) {
  auto ret = ID, sq = m;
  for(; ex>0; ex>>=1, sq *= sq)
    if(ex&1) ret *= sq;
  return ret;
}

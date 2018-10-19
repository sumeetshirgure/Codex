#pragma once

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define ff first
#define ss second
const char nl = '\n';
/* -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- */
#include <bits/extc++.h>
namespace pbds =  __gnu_pbds;
template <typename key, typename val=pbds::null_type, typename comp=less<key> >
using ostree = pbds::tree<key, val, comp, pbds::rb_tree_tag,
                          pbds::tree_order_statistics_node_update>;
using vi = vector< int >; using vll = vector< ll >;
#define allOf(x) std::begin(x), std::end(x)
template <typename...Args>
ostream&operator<<(ostream&os, pair<Args...> const &p)
{return os<<'('<<p.first<<", "<<p.second<<')';}
template <typename...Args>
ostream&operator<<(ostream&os, vector<Args...> const &v)
{os<<'[';for(const auto&el:v)os<<' '<<el;return(os<<" ]");}
template <typename...Args> ostream&operator<<(ostream&os, map<Args...>const&v)
{os<<'[';for(auto const&el:v)os<<' '<<el;return(os<<" ]");}
template <typename...Args> ostream&operator<<(ostream&os, set<Args...>const&v)
{os<<'[';for(auto const&el:v)os<<' '<<el;return(os<<" ]");}
template <typename...Args>
ostream&operator<<(ostream&os, unordered_map<Args...>const&v)
{os<<'[';for(auto const&el:v)os<<' '<<el;return(os<<" ]");}
template<typename T> void trace_rec(stringstream&sst, const T&t)
{ string arg; getline(sst, arg, ','); cerr << arg << " : " << t << " }"; }
template<typename T, typename... Args>
void trace_rec(stringstream&sst, const T&t, const Args... args)
{ string arg; getline(sst, arg, ','); cerr << arg << " : " << t << ", ";
  trace_rec(sst, args...); }
template<typename... Args> void trace(const string&s, Args... args)
{stringstream sst(s); cerr << "{ "; trace_rec(sst, args...); cerr << endl;}
#define dbg(...) trace(#__VA_ARGS__, __VA_ARGS__)
template <typename T> void dbr(const T lb, const T ub)
{cerr<<'{';for(auto it=lb; it!=ub; it++)cerr<<' '<<(*it);cerr<<" }"<<endl;}
template<typename T, typename Comp=less<T> >
bool setMin(T &mem, const T&v, Comp comp = Comp())
{ return comp(v, mem) ? mem = v, true : false; }
template<typename T, typename Comp=less<T> >
bool setMax(T &mem, const T&v, Comp comp = Comp())
{ return comp(mem, v) ? mem = v, true : false; }
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

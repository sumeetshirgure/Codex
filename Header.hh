#pragma once

#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
using ll = long long; using ld = long double; const char nl = '\n';
/* -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- */
#include <bits/extc++.h>
namespace pbds =  __gnu_pbds;
template <typename key, typename val=pbds::null_type, typename comp=less<key>>
using ostree=pbds::tree<key,val,comp,pbds::rb_tree_tag,pbds::tree_order_statistics_node_update>;
using vi = vector< int >; using vll = vector< ll >;
#define all(x) std::begin(x), std::end(x)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename...Args, template<typename...> typename T> string to_string(T<Args...> const&);
string to_string(string const&s){return '"'+s+'"';}
string to_string(char const &c) {return to_string(string(1,c));}
string to_string(char const *c) {return to_string(string(c));}
string to_string(bool const &b) {return (b ? "1" : "0");}
template<typename... Args> string to_string(pair<Args...> const&p)
{return "("+to_string(p.first)+", "+to_string(p.second)+")";}
template <typename...Args, template<typename...> typename T> string to_string(T<Args...> const&S)
{string s = "{"; for(auto const& e: S)s+=" "+to_string(e);s+=" }"; return s;}
template<typename Tail> void debug_out(Tail t) {cerr<<" "<<to_string(t)<<" ]"<<endl;}
template<typename Head, typename... Tail> void debug_out(Head h, Tail... t)
{cerr << " " << to_string(h) << ","; debug_out(t...);}
#define pr(...) cerr<<"["<<(#__VA_ARGS__)<<"] : [", debug_out(__VA_ARGS__)
template <typename T> void dbr(T lb, T ub)
{cerr<<'{';for(auto it=lb; it!=ub; it++)cerr<<' '<<to_string(*it); cerr<<" }"<<endl;}
template<typename T, typename Comp=less<T>> bool setMin(T &mem, const T&v, Comp comp = Comp())
{return comp(v, mem) ? mem = v, true : false;}
template<typename T, typename Comp=less<T>> bool setMax(T &mem, const T&v, Comp comp = Comp())
{return comp(mem, v) ? mem = v, true : false;}

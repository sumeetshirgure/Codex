#pragma once

/* Dynamic convex hull structure. */
const ll INF = (ll)9e18;
const static int LX = -(1e9), RX = 1e9;
struct Dynamic_Hull { /* Max hull */
  struct Line{
    ll m, c; // slope, intercept
    Line(ll mm=0, ll cc=-INF) { m = mm; c = cc; }
    ll operator[](const int&x){ return m*x+c; }
  };
  struct node {
    node *lt,*rt; Line ln; 
    node(const Line &l){lt=rt=nullptr; ln=l;} 
  };
  node *root=nullptr;

  void add(Line l,node*&it,int lx=LX,int rx=RX){
    if(it==nullptr)it=new node(l);
    if(it->ln[lx]>=l[lx] and it->ln[rx]>=l[rx]) return;
    if(it->ln[lx]<=l[lx] and it->ln[rx]<=l[rx]) {it->ln=l; return;}
    int mid = (lx+rx)>>1;
    if(it->ln[lx] < l[lx]) swap(it->ln,l);
    if(it->ln[mid] >= l[mid]) add(l,it->rt,mid+1,rx);
    else { swap(it->ln,l); add(l,it->lt,lx,mid); }
  }
  void add(const ll &m,const ll &c) { add(Line(m,c),root); }

  ll get(int &x,node*&it,int lx=LX,int rx=RX){
    if(it==NULL) return -INF; // Max hull
    ll ret = it->ln[x]; 
    int mid = (lx+rx)>>1;
    if(x<=mid) ret = max(ret , get(x,it->lt,lx,mid));
    else ret = max(ret , get(x,it->rt,mid+1,rx));
    return ret;
  }
  ll get(int x){ return get(x,root); }
};

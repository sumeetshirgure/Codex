#pragma once

template<typename FlowType=int>
struct FlowNet {
  FlowType const static MAXF = (FlowType)(1e9);

  int n;
  vector< FlowType > resf, caps;
  vector< vector< pair<int, int> > > adj;
  vector< int > ptr, dist, Q;
  FlowNet(int const &nodes=0) : n(nodes), adj(nodes), ptr(nodes), dist(nodes), Q(nodes) { }

  void add_edge(int from, int to, FlowType cap=MAXF, bool bidirectional=false) {
    int edge_id = resf.size();
    adj[from].emplace_back(to, edge_id);
    adj[to].emplace_back(from, edge_id^1);
    resf.emplace_back(cap);
    resf.emplace_back(bidirectional ? cap : 0);
    caps.emplace_back(cap);
    caps.emplace_back(bidirectional ? cap : 0);
  }

  bool bfs(int src, int sink) {
    fill(dist.begin(), dist.end(), n);
    int lx = 0, rx = 0;
    dist[src] = 0, Q[rx++] = src;
    for(int u; lx<rx;) { u = Q[lx++];
      for(auto e: adj[u]) {
        int v = e.first, id = e.second;
        if( dist[v] < n or resf[id] == 0 ) continue;
        dist[v] = dist[u] + 1, Q[rx++] = v;
      }
    }
    return dist[sink] < n;
  }

  FlowType dfs(int u, int sink, FlowType flow = MAXF) {
    if( flow == 0 or u == sink ) return flow;
    for(int&cur=ptr[u]; cur<(int)adj[u].size(); cur++) {
      int v = adj[u][cur].first, eid = adj[u][cur].second;
      if( dist[v] != dist[u] + 1 ) continue;
      int df = dfs(v, sink, min(flow, resf[eid]));
      if( df > 0 ) { resf[eid] -= df, resf[eid^1] += df; return df; }
    }
    return 0;
  }

  auto maxflow(int source, int sink) {
    FlowType max_flow = 0, pushed;
    while( bfs(source, sink) ) {
      fill(ptr.begin(), ptr.end(), 0);
      while( (pushed = dfs(source, sink)) > 0 ) max_flow += pushed;
    }
    return max_flow;
  }

  auto mincut(int source, int sink) {
    maxflow(source, sink);
    vector< int > ret(n); iota(all(ret), 0);
    ret.erase(remove_if(all(ret), [&](int node){ return dist[node] == n; }), ret.end());
    return ret;
  }

  auto flow() {
    vector< tuple<int,int,FlowType> > flows;
    for(int i=0; i<n; i++)
      for(auto e: adj[i]) {
        auto df = caps[e.second] - resf[e.second];
        if( df > 0 ) flows.emplace_back(i, e.first, df);
      }
    return flows;
  }

};

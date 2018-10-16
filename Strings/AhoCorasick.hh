#pragma once
#include "../Header.hh"

/* Aho-Corasick prefix automaton. */
namespace AhoCorasick {
  const string alphabet = "abcdefghijklmnopqrstuvwxyz";
  const int CS = 26;

  struct TrieNode {
    int go[CS], dfa[CS], fail, par; char in;
    vector<int> op;
    TrieNode(int par=-1, char c='$') : par(par), in(c) {
      fill(go, go+CS, -1);
      fill(dfa, dfa+CS, -1);
      fail = -1;
    }
    int& operator[](const char&c){ return go[c-'a']; }
    int& operator()(const char&c){ return dfa[c-'a']; }
  };

  struct Automaton {
    vector<TrieNode> trie;

    int get_next(const int&state, const char&c) {
      if( trie[state][c] == -1 ) {
        trie[state][c] = (int)trie.size();
        trie.emplace_back(TrieNode(state, c));
      }
      return trie[state][c];
    }

    void add_string(const int&key, const string &s) {
      int state = 0;
      for(const auto& c: s) state = get_next(state, c);
      trie[state].op.emplace_back(key);
    }

    Automaton(const vector<string> &v, const bool& build_dfa=true) {
      trie.emplace_back(TrieNode()); // Make root and trie.
      for(int idx=0; idx<(int)v.size(); idx++) add_string(idx, v[idx]);
      int buf[trie.size()], lptr = 0, rptr = 0; // Run BFS.
      for(const char&c : alphabet)
        if( trie[0][c] == -1 ) trie[0][c] = 0; // To terminate pi-loop.
        else trie[ trie[0][c] ].fail = 0, buf[rptr++] = trie[0][c];
      for(int u=buf[lptr], v, sf; lptr<rptr; u=buf[++lptr]) {
        for(const char&c: alphabet) {
          v = trie[u][c];
          if( v == -1 ) continue;
          buf[rptr++] = v;
          for(sf=trie[u].fail; trie[sf][c] == -1; sf=trie[sf].fail); // pi-loop.
          trie[v].fail = trie[sf][c]; // Update suffix link.
          for(auto &id: trie[ trie[v].fail ].op) trie[v].op.emplace_back(id);
        }
      }
      if( not build_dfa ) return;
      lptr = rptr = 0;
      for(const char&c: alphabet) {
        int child = (trie[0](c) = trie[0][c]);
        if( child != 0 ) buf[rptr++] = child;
      }
      for(int u=buf[lptr], v; lptr<rptr; u=buf[++lptr]) {
        for(const char&c: alphabet) {
          v = trie[u][c];
          if( v == -1 ) trie[u](c) = trie[ trie[u].fail ](c);
          else trie[u](c) = v, buf[rptr++] = v;
        }
      }
    }

    void mark_counts(const string &pat, vector<int> &counts) {
      int state = 0;
      for(const char &area: pat) {
        state = trie[state](area);
        for(auto &id: trie[state].op) counts[id]++;
      }
    }

  };

};

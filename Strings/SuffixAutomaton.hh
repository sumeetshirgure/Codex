#pragma once
#include "../Header.hh"

/* Suffix automaton. */
namespace SuffixAutomaton {
  const int CS = 26;

  struct State {
    int dfa[CS], link, len, par; 
    char in; 
    bool cloned, term;
    State(int par=-1, char c='$') : par(par), in(c), cloned(false), term(false)
    { fill(dfa, dfa+CS, -1); link = 0; }
    int& operator[](const char &c) { return dfa[c-'a']; }
  };

  struct Automaton {
    int last;
    vector< State > st;

    void extend_aut(const char &c) {
      int cur = (int)st.size(), p = last; 
      st.emplace_back(State(last, c));
      st[cur].len = st[last].len + 1;
      last = cur;
      for(; p!=-1 and st[p][c]==-1; p=st[p].link) st[p][c] = cur;
      if( p == -1 ) { st[cur].link = 0; } else {
        int q = st[p][c];
        if( st[q].len == st[p].len + 1 ) { st[cur].link = q; } else {
          int clone = (int)st.size();
          st.emplace_back(st[q]);
          st[clone].len = st[p].len + 1;
          st[clone].cloned = true;
          for(; p!=-1 and st[p][c] == q; p=st[p].link) st[p][c] = clone;
          st[q].link = st[cur].link = clone;
        }
      }
    }

    bool is_suffix(const string&pat) {
      int state = 0;
      for(const char c: pat) {
        state = st[state][c];
        dbg(c, state);
        if( state == -1 ) return false;
      }
      return st[state].term;
    }

    Automaton(const string&s) {
      st.emplace_back(State());
      last = 0; st[0].len = 0; st[0].link = -1;
      for(const char c: s) extend_aut(c);
      for(int state = last; state != -1; state = st[state].link)
        st[state].term = true;
    }
  };

};

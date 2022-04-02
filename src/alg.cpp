// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int prior(char op) {
  switch (op) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
      return 2;
    case '-':
      return 2;
    case '/':
      return 3;
    case '*':
      return 3;
    case ' ':
      return 5;
    default:
      return 4;
  }
}
int calculate(char op, int x, int y) {
  switch (op) {
      case '+':
        return y+ x;
      case '-':
        return y - x;
      case '*':
        return y * x;
      case '/':
        if (x != 0)
          return y / x;
      default:
        return 0;
  }
}

std::string infx2pstfx(std::string inf) {
  std::string post;
  char prob = ' ';
  TStack <char, 100> t;
  for (int a = 0; a < inf.size(); a++) {
    if (prior(inf[a]) == 4) {
      post.push_back(inf[a]);
      post.push_back(prob);
    } else {
      if (prior(inf[a]) == 0) {
        t.push(inf[a]);
      } else if (t.isEmpty()) {
        t.push(inf[a]);
      } else if ((prior(inf[a]) > prior(t.get()))) {
        t.push(inf[a]);
      } else if (prior(inf[a]) == 1) {
        while (prior(t.get()) != 0) {
          post.push_back(t.get());
          post.push_back(prob);
          t.pop();
        }
        t.pop();
      } else {
        while (!t.isEmpty() && (prior(inf[a]) <= prior(t.get()))) {
          post.push_back(t.get());
          post.push_back(prob);
          t.pop();
        }
        t.push(inf[a]);
      }
    }
  }
  while (!t.isEmpty()) {
    post.push_back(t.get());
    post.push_back(prob);
    t.pop();
  }
  for (int b = 0; b < post.size(); b++) {
    if (post[post.size()-1] == ' ')
      post.erase(post.size()-1);
  }
  return post;
}

int eval(std::string pref) {
  TStack <int, 100> t;
  int res = 0;
  for (int a = 0; a < pref.size(); a++) {
    if (prior(pref[a]) == 4) {
      t.push(pref[a] - '0');
    } else if (prior(pref[a]) < 4) {
      int x = t.get();
      t.pop();
      int y = t.get();
      t.pop();
      t.push(calculate(pref[a], x, y));
    }
  }
  res = t.get();
  return res;
}

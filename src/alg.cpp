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
int calculate(char op, int a, int b) {
  switch (op) {
      case '+':
        return b + a;
      case '-':
        return b - a;
      case '*':
        return b * a;
      case '/':
        if (a != 0)
          return b / a;
      default:
        return 0;
  }
}

std::string infx2pstfx(std::string inf) {
  std::string post;
  char prob = ' ';
  TStack <char, 100> t;
  for (int i = 0; i < inf.size(); i++) {
    if (prior(inf[i]) == 4) {
      post.push_back(inf[i]);
      post.push_back(prob);
    } else {
      if (prior(inf[i]) == 0) {
        t.push(inf[i]);
      } else if (t.isEmpty()) {
        t.push(inf[i]);
      } else if ((prior(inf[i]) > prior(t.get()))) {
        t.push(inf[i]);
      } else if (prior(inf[i]) == 1) {
        while (prior(t.get()) != 0) {
          post.push_back(t.get());
          post.push_back(prob);
          t.pop();
        }
        t.pop();
      } else {
        while (!t.isEmpty() && (prior(inf[i]) <= prior(t.get()))) {
          post.push_back(t.get());
          post.push_back(prob);
          t.pop();
        }
        t.push(inf[i]);
      }
    }
  }
  while (!t.isEmpty()) {
    post.push_back(t.get());
    post.push_back(prob);
    t.pop();
  }
  for (int j = 0; j < post.size(); j++) {
    if (post[post.size()-1] == ' ')
      post.erase(post.size()-1);
  }
  return post;
}

int eval(std::string pref) {
  TStack <int, 100> t;
  int res = 0;
  for (int i = 0; i < pref.size(); i++) {
    if (prior(pref[i]) == 4) {
      t.push(pref[i] - '0');
    } else if (prior(pref[i]) < 4) {
      int x = t.get();
      t.pop();
      int y = t.get();
      t.pop();
      t.push(calculate(pref[i], x, y));
    }
  }
  res = t.get();
  return res;
}

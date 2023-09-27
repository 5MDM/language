#ifndef SYNTAX_ANALYZER_HPP_
#define SYNTAX_ANALYZER_HPP
#include <vector>
#include <iostream>
#include "token.hpp"
#include "error.hpp"
#define PREV tokens[i-1]
#define NEXT tokens[i+1]
#define CHECK_FILE if(i == 0) { \
  throw mderr_syntax(0, 0, "Lefthand side of operator is BOF"); \
} else if(i+1 == tokens.size()) { \
  throw mderr_syntax(0, 0, "Righthand side of operator is EOF"); \
} else if(tokens[i-1].type == SEMICOLON) { \
  throw mderr_syntax(0, 0, "Lefthand side of operator is a semicolon"); \
} else if(tokens[i+1].type == SEMICOLON) { \
  throw mderr_syntax(0, 0, "Righthand side of operator is a semicolon"); \
}

using namespace std;

void analyze_syntax(vector<Token> tokens) {
  for(int i = 0; i != tokens.size(); i++) {
    Token now = tokens[i];
    if(now.type == OPERATOR_DOUBLE) {
      CHECK_FILE;
      
    } else if(now.type == OPERATOR_DOUBLE_ASSIGNMENT) {
      CHECK_FILE;
      if(PREV.type != IDENTIFIER) {
        throw mderr_syntax(0, 0, "Assignment operator cannot be used on non-identifiers");
      }
    }
  }
}

#undef PREV
#undef NEXT
#undef CHECK_FILE
#endif
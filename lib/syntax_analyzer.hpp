#include <vector>
#include <iostream>
#include "token.hpp"
#include "error.hpp"
#define PREV tokens[i-1];
#define NEXT tokens[i+1];

using namespace std;

void analyze_syntax(vector<Token> tokens) {
  for(int i = 0; i != tokens.size(); i++) {
    Token now = tokens[i];
    if(now.type == OPERATOR_DOUBLE) {
      if(i == 0) {
        throw mderr_syntax(0, 0, "Lefthand side of operator is BOF");
      } else if(i+1 == tokens.size()) {
        throw mderr_syntax(0, 0, "Righthand side of operator is EOF"); 
      }
    }
  }
}
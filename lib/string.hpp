#ifndef STRING_HPP_
#define STRING_HPP_
#include "token.hpp"
#include "error.hpp"
#include <string>

uintmax_t parse_string
(Token* token, char* buffer, uintmax_t i, uintmax_t file_length) {
  token->type = STRING;
  string s;
  
  while(++i < file_length) {
    const char c = buffer[i];
    if(c == '\\') {
      switch(buffer[++i]) {
        case '\\': s += '\\'; break;
        case 'n': s += '\n'; break;
        case '"': s += '"'; break;
        default: throw runtime_error("Invalid escape");
      }
    } else if(c != '"') {
      s += c;
    } else {
      break;
    }
  }
  
  if(i >= file_length) mderr_syntax(0, 0, "Unexpected EOF");
  
  
  token->value = s;
  
  return i;
}

#endif
#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>
#include <string>

const string mderr_color = "\033[31m";
const string mderr_reset = "\033[0m";

void mderr_base(uintmax_t line, uintmax_t column, const char* type, const char* reason) {
  cout << mderr_color << "MDIL Error " << line << ":" << column 
  << '\n' << "  type: " << type << '\n' << "  reason: " 
  << reason << mderr_reset << '\n';
}

string mderr_syntax(uintmax_t line, uintmax_t column, const char* reason) {
  mderr_base(line, column, "syntax", reason);
  return "\n";
}

#endif
#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>
#include <string>
#include <sstream>

const string mderr_color = "\033[31m";
const string mderr_reset = "\033[0m";

string mderr_base(uintmax_t line, uintmax_t column, const char* type, const char* reason) {
  ostringstream oss;
  oss << mderr_color << "MDIL Error " << line << ":" << column 
  << '\n' << "  type: " << type << '\n' << "  reason: " 
  << reason << mderr_reset << "\n\n";
  return oss.str();
}

string mderr_syntax(uintmax_t line, uintmax_t column, const char* reason) {
  return mderr_base(line, column, "syntax", reason);
}

#endif
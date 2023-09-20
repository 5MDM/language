#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>

void mderr_base(uintmax_t line, uintmax_t column, const char* type, const char* reason) {
  cout << "MDIL Error " << line << ":" << column << '\n'
  << "  type: " << type << '\n' << "  reason: " << reason << '\n';
}

void mderr_syntax(uintmax_t line, uintmax_t column, const char* reason) {
  mderr_base(line, column, "syntax", reason);
}

#endif
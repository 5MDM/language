#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <string>

enum Token_type {
  STRING,
  NUMBER,
  OPERATOR,
  KEYWORD,
  BLOCK_START,
  BLOCK_END,
  IDENTIFIER
};

struct Token {
  Token_type type;
  string value;
};

const char TOKEN_OPERATORS[] = {'+', '-', '*', '/', '=', '!', '<', '>'};

const char TOKEN_NUMBERS_START[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

const char TOKEN_NUMBERS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

const char TOKEN_BLOCKS_START[] = {'(', '[', '{', '<'};
const char TOKEN_BLOCKS_END[] = {')', ']', '}', '>'};

const char TOKEN_SEPERATOR[] = {',', ' ', '\n', ';'};

const char* TOKEN_KEYWORDS[] = {
  "let", "const"
};

#endif
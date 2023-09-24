#ifndef TOKENIZER_HPP_
#define TOKENIZER_HPP_
#include <string>
#include <vector>
#include <cstring>
#include "error.hpp"
#include "token.hpp"
#include "string.hpp"
#define LOOP_C(c, arr, f) { \
  for(int loop_i = 0; loop_i < sizeof(arr); loop_i++) { \
    if(c == arr[loop_i]) f \
  } \
}

#define LOOP_S(s, arr, f) { \
  for(int loop_i = 0; loop_i < sizeof(arr); loop_i++) { \
    if(s.compare(arr[loop_i]) == 0) f \
  } \
}


using namespace std;

void debug_token(vector<Token> arr) {
  uintmax_t num = 0;
  for(Token i : arr) {
    cout << "\nToken " << num << ":\n";
    cout << "  type- " << i.type << '\n';
    cout << "  value- " << i.value << '\n';
    num++;
  }
}

char string_escape(char c);
uintmax_t string_parse
(vector<Token> arr, char* buffer, uintmax_t i, uintmax_t file_length);

void fileline_parse
(vector<int> fileline, char* buffer, uintmax_t file_length) {
  int line = 0;
  for(uintmax_t i = 0; i < file_length; i++) {
    const char c = buffer[i];
    if(c == '\n') {
      fileline.push_back(line);
      line = 0;
    } else {
      line++;
    }
  }
  
  fileline.push_back(line);
}

void tokenize
(char* buffer, uintmax_t file_length, vector<Token>* token_arr) {
  
  vector<int> fileline;
  fileline_parse(fileline, buffer, file_length);
  
  int line_number = 0;
  int blocks_start_amnt = 0;
  int blocks_end_amnt = 0;
  string current;
  
  for(uintmax_t i = 0; i < file_length; i++) {
    
    char c = buffer[i];
    
    LOOP_C(c, TOKEN_OPERATORS_DOUBLE, {
      Token token;
      token.type = OPERATOR_DOUBLE;
      if(buffer[i+1] == '=') {
        string s;
        s += c;
        s += '=';
        token.value = s;
        i++;
      } else {
        token.value = c;
      }
    
      token_arr->push_back(token);
      goto next_character;
    });
    
    if(c == '"') {
      Token token;
      i = parse_string(&token, buffer, i, file_length);
      token_arr->push_back(token);
      goto next_character;
    }
    
    LOOP_C(c, TOKEN_NUMBERS_START, {
      Token token;
      token.type = NUMBER;
      string s;
      bool isDecimal = false;
      while(i < file_length+1) {
        bool found = false;
        LOOP_C(buffer[i], TOKEN_NUMBERS, {
          if(buffer[i] == '.') {
            if(isDecimal) {
              throw mderr_syntax(0, 0, "More than one decimal point");
            } else {
              isDecimal = true;
            }
          }
          s += buffer[i++];
          found = true;
          break;
        });
        
        if(!found) {
          token.value = s;
          token_arr->push_back(token);
          i--;
          goto next_character;
        }
      }
    });
    
    LOOP_C(c, TOKEN_BLOCKS_START, {
      Token token;
      token.type = BLOCK_START;
      token.value = c;
      token_arr->push_back(token);
      blocks_start_amnt++;
      goto next_character;
    });
    
    LOOP_C(c, TOKEN_BLOCKS_END, {
      Token token;
      token.type = BLOCK_END;
      token.value = c;
      token_arr->push_back(token);
      blocks_end_amnt++;
      goto next_character;
    });

    {
      bool is_whitespace = false;
      LOOP_C(buffer[i], TOKEN_SEPERATOR, {
        is_whitespace = true;
        break;
      });
      
      if(!is_whitespace) {
        string identifier;
        while(i < file_length+1) {
          bool ended = false;
          LOOP_C(buffer[i], TOKEN_SEPERATOR, {
            ended = true;
          });
          
          if(ended) {
            break;
          } else {
            identifier += buffer[i];
            i++;
          }
        }
        
        Token token;
        token.value = identifier;
        
        bool isKeyword = false;
        LOOP_S(identifier, TOKEN_KEYWORDS, {
          isKeyword = true;
          break;
        });
        
        if(isKeyword) {
          token.type = KEYWORD;
          cout << "Keyword: " << identifier << '\n';
        } else {
          token.type = IDENTIFIER;
          cout << "Identifier: " << identifier << '\n';
        }
        token_arr->push_back(token);
      }
    }
    
    next_character:
    continue;
  }
  
  if(blocks_start_amnt > blocks_end_amnt) {
    throw mderr_syntax(0, 0, "Improperly closed blocks, there are more opening blocks then ending blocks");
  } else if(blocks_start_amnt < blocks_end_amnt) {
    throw mderr_syntax(0, 0, "Improperly closed blocks, there are more ending blocks than opening blocks");
  }
}

#endif
#include <iostream>
#include <filesystem>
#include <vector>
#include "lib/read_file.hpp"
#include "lib/tokenizer.hpp"
#include "lib/syntax_analyzer.hpp"

using namespace std;

int main() {
  filesystem::path file_name = "index.mdil";
  uintmax_t file_size = get_file_size(file_name);
  
  char main_file[file_size];
  read_file(main_file, file_name, file_size);
  
  try {
    vector<Token> token_arr;
    tokenize(main_file, file_size, &token_arr);
    analyze_syntax(token_arr);
  } catch(const string err) {
    cout << err << '\n';
  }
  
  return 0;
}
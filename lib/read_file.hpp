#ifndef READ_FILE_HPP_
#define READ_FILE_HPP_
#include <fstream>
#include <filesystem>

using namespace std;

uintmax_t get_file_size
(filesystem::path file_path) {
  uintmax_t size = 
  filesystem::file_size(file_path);
  return size;
}

void read_file
(char* buffer, filesystem::path file_path, uintmax_t file_size) {
  ifstream stream;
  stream.open(file_path);
  
  if(stream.bad()) {
    throw runtime_error(
      "Can't read file " + (string) file_path
    );
  } else if(stream.is_open()) {
    stream.read(buffer, file_size);
    buffer[file_size] = '\0';
    stream.close();
  } else {
    throw runtime_error(
      "File error with: " + (string) file_path
    );
  }
}

#endif
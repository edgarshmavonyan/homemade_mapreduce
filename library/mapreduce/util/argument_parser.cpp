#include "argument_parser.h"

#include <iostream>
#include <sstream>

std::tuple<std::string, std::string, size_t> ParseArguments(int argc, char* argv[]) {
  if (argc != 4) {
    throw std::exception();
  }

  std::string input_path(argv[1]);
  std::string output_directory(argv[2]);
  size_t reducer_number;
  std::stringstream stringstream(argv[3]);
  stringstream >> reducer_number;
  return std::make_tuple(input_path, output_directory, reducer_number);
}
#pragma once
#include <string>
#include <tuple>

std::tuple<std::string, std::string, size_t> ParseArguments(int argc, char* argv[]);
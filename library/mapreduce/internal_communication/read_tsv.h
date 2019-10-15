#pragma once
#include "util/filesystem.h"

#include <fstream>
#include <vector>

template<typename Key, typename Value>
std::vector<std::pair<Key, Value>> ReadTSV(const fs::path& file_path) {
  std::vector<std::pair<Key, Value>> result;
  std::ifstream stream(file_path);
  while (stream.good()) {
    Key key;
    stream >> key;
    if (stream.good()) {
      Value value;
      stream >> value;
      result.emplace_back(std::move(key), std::move(value));
    }
  }
  return result;
}

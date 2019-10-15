#pragma once
#include <iostream>

constexpr size_t MAX_FILEPATH = 4000;

//TODO: decide if can be written more effective. (Serialization?)
class Slice {
 public:
  Slice();
  Slice(std::string path, size_t start, size_t end = -1);

  const char* GetPath() const;
  size_t GetStart() const;
  size_t GetEnd() const;

 private:
  char path_[MAX_FILEPATH];
  size_t start_;
  size_t end_;
};
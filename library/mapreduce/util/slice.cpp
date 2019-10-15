#include "slice.h"

#include <cstring>

Slice::Slice()
  : start_()
  , end_() {
}

Slice::Slice(std::string path, size_t start, size_t end)
  : start_(start)
  , end_(end) {
  strncpy(path_, path.c_str(), MAX_FILEPATH);
}

const char* Slice::GetPath() const {
  return path_;
}

size_t Slice::GetStart() const {
  return start_;
}

size_t Slice::GetEnd() const {
  return end_;
}
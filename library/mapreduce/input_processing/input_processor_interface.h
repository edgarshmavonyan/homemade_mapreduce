#pragma once
#include "util/slice.h"

#include <vector>
#include <string>
#include <tuple>

using SlicedInput = std::vector<Slice>;

class InputProcessorInterface {
 public:
  virtual SlicedInput Process() = 0;
  virtual ~InputProcessorInterface() = 0;
};

// TODO: new file
class AbstractFixedSizeProcessor: public InputProcessorInterface {
 public:
  explicit AbstractFixedSizeProcessor(size_t slice_size);
 protected:
  const size_t slice_size_;
};
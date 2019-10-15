#pragma once
#include "input_processing/input_processor_interface.h"

class InputSender {
 public:
  InputSender(
      const SlicedInput& sliced_input, size_t world_size,
      size_t world_start, bool process_myself = false);

  void Send() const;

 private:
  const SlicedInput& sliced_input_;
  size_t world_size_;
  size_t world_start_;
  bool process_myself_;
};
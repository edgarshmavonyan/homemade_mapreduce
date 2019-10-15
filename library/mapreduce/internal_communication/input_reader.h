#pragma once
#include "util/slice.h"
#include "operation_input.h"

#include <vector>

class InputReader: public OperationInputInterface<std::string> {
 public:
  explicit InputReader(int head_rank);

  bool Receive();

  void Next() override;
  const std::string& Get() const override;

  bool IsValid() const override;

 private:
  void CacheCurrentSlice();

 private:
  int head_rank_;
  std::vector<Slice> data_slices_;
  std::string cur_block_;
  size_t cur_index_;
  bool initialized_;
};
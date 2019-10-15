#pragma once
#include "operation_input.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <string_view>

template<typename Key, typename Value>
class ReducerInput: public OperationInputInterface<Value> {
 public:
  explicit ReducerInput(std::istream& stream);

  void Next() override {
    ++cur_index_;
  }

  bool IsValid() const override {
    return cur_index_ < data_.size();
  }

  const Value& Get() const override {
    return data_[cur_index_];
  }

  const Key& GetKey() const {
    return key_;
  }

 private:
  Key key_;
  std::vector<Value> data_;
  size_t cur_index_;
};

template<typename Key, typename Value>
ReducerInput<Key, Value>::ReducerInput(std::istream& stream)
  : cur_index_(0) {
  std::string line;
  std::getline(stream, line);
  std::stringstream line_stream;
  line_stream << line;
  line_stream >> key_;
  while (line_stream.good()) {
    data_.emplace_back();
    line_stream >> data_.back();
  }
}
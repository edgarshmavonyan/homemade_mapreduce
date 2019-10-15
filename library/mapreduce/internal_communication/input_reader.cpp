#include "input_reader.h"

#include <mpi.h>

#include <fstream>

InputReader::InputReader(int head_rank)
  : head_rank_(head_rank)
  , initialized_(false) {
}

bool InputReader::Receive() {
  if (initialized_) {
    return false;
  }
  MPI_Status status;
  MPI_Probe(head_rank_, 1, MPI_COMM_WORLD, &status);

// TODO: change to MPI Type create struct
  int char_count;
  MPI_Get_count(&status, MPI_CHAR, &char_count);
  size_t vector_size = char_count / sizeof(Slice);
  data_slices_.resize(vector_size);

  MPI_Recv(
      data_slices_.data(),
      char_count, MPI_CHAR,
      head_rank_, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  cur_index_ = 0;
  initialized_ = true;
  CacheCurrentSlice();
  return true;
}

void InputReader::Next() {
  ++cur_index_;
  if (IsValid()) {
    CacheCurrentSlice();
  }
}

const std::string& InputReader::Get() const {
  return cur_block_;
}

bool InputReader::IsValid() const {
  return initialized_ && cur_index_ < data_slices_.size();
}

void InputReader::CacheCurrentSlice() {
  std::ifstream stream(data_slices_[cur_index_].GetPath());
  stream.seekg(data_slices_[cur_index_].GetStart());
  cur_block_.resize(data_slices_[cur_index_].GetEnd() - data_slices_[cur_index_].GetStart());
  stream.read(&cur_block_[0], cur_block_.size());
}

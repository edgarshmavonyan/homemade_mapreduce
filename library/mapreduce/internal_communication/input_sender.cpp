#include "input_sender.h"

#include <mpi.h>

InputSender::InputSender(
    const SlicedInput& sliced_input, size_t world_size,
    size_t world_start, bool process_myself)
  : sliced_input_(sliced_input)
  , world_size_(world_size)
  , world_start_(world_start)
  , process_myself_(process_myself) {
  if (process_myself_) {
    // TODO: delete or implement logic
    throw std::exception();
  }
}

void InputSender::Send() const {
  size_t chunk_size = sliced_input_.size() / world_size_;
  // leftovers to the first process
  size_t cur_size = chunk_size + sliced_input_.size() % world_size_;

  int dest = world_start_;
  for (size_t i = 0; i < sliced_input_.size(); i += cur_size) {
    if (i == 0 && process_myself_) {
      i += cur_size;
    } else {
      MPI_Send(&sliced_input_[i],
               cur_size * sizeof(Slice),
               MPI_CHAR,
               dest,
               1,
               MPI_COMM_WORLD);
    }
    ++dest;
    cur_size = chunk_size;
  }

}

#include "input_processor_interface.h"


InputProcessorInterface::~InputProcessorInterface() = default;

AbstractFixedSizeProcessor::AbstractFixedSizeProcessor(size_t slice_size)
  : slice_size_(slice_size) {
}
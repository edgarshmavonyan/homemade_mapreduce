#include "process.h"

#include "dir_processor.h"
#include "file_processor.h"

#include "util/filesystem.h"

const size_t kSliceSize = 1024 * 4;

SlicedInput ProcessInput(const std::string& input_path) {
  fs::path path(input_path);
  InputProcessorInterface* processor = nullptr;
  if (fs::is_directory(input_path)) {
    processor = new DirProcessor(input_path, kSliceSize);
  } else {
    processor = new FileProcessor(input_path, kSliceSize);
  }
  SlicedInput result = processor->Process();
  delete processor;
  return result;
}
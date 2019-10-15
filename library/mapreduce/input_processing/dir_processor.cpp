#include "dir_processor.h"

#include "file_processor.h"
#include "util/filesystem.h"

DirProcessor::DirProcessor(std::string path, size_t slice_size)
  : dir_path_(std::move(path))
  , AbstractFixedSizeProcessor(slice_size) {
}

DirProcessor::~DirProcessor() = default;

const std::string& DirProcessor::GetDirPath() const {
  return dir_path_;
}

SlicedInput DirProcessor::Process() {
  SlicedInput result;

  fs::directory_iterator directory(dir_path_);
  for (auto& file : directory) {
    FileProcessor cur_file_processor(file.path(), slice_size_);
    SlicedInput file_input = cur_file_processor.Process();
    result.insert(result.end(), file_input.begin(), file_input.end());
  }
  return result;
}

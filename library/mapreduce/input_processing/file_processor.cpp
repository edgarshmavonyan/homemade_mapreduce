#include "file_processor.h"

FileProcessor::FileProcessor(std::string path, size_t slice_size)
  : path_(std::move(path))
  , AbstractFixedSizeProcessor(slice_size) {
}

FileProcessor::~FileProcessor() = default;

const std::string& FileProcessor::GetPath() const {
  return path_;
}

SlicedInput FileProcessor::Process() {
  SlicedInput result;
  std::string temp_input;
  size_t cur_start = 0, cur_end = 0;

  std::ifstream file_stream(path_);
  while (!file_stream.eof()) {
    while (!file_stream.eof() && cur_end - cur_start < slice_size_) {
      std::getline(file_stream, temp_input);
      cur_end += temp_input.size();
      if (!file_stream.eof()) {
        ++cur_end;
      }
    }
    result.emplace_back(path_, cur_start, cur_end);
    cur_start = cur_end;
  }
  file_stream.close();
  return result;
}

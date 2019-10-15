#pragma once
#include "util/slice.h"
#include "util/filesystem.h"
#include "internal_communication/filenames.h"

#include <fstream>

template<typename Key, typename Value>
class OutputWriter {
 public:
  OutputWriter(const std::string& base_path, int process_rank);
  OutputWriter(fs::path output_file_path);

  std::string GetFileName() const;

  void Write(const std::pair<Key, Value>& kv_pair);

 private:
  fs::path file_path_;
  std::ofstream stream_;
};

template<typename Key, typename Value>
OutputWriter<Key, Value>::OutputWriter(const std::string& base_path, int process_rank)
    : file_path_(base_path) {
  fs::create_directory(file_path_);
  file_path_ /= GetMapperOutputFileName(process_rank);
  stream_ = std::ofstream(file_path_);
}

template<typename Key, typename Value>
OutputWriter<Key, Value>::OutputWriter(fs::path output_file_path)
    : file_path_(std::move(output_file_path))
    , stream_(file_path_) {
}

template<typename Key, typename Value>
std::string OutputWriter<Key, Value>::GetFileName() const {
  return file_path_.string();
}

template<typename Key, typename Value>
void OutputWriter<Key, Value>::Write(const std::pair<Key, Value>& kv_pair) {
  stream_ << kv_pair.first << '\t' << kv_pair.second << '\n';
}

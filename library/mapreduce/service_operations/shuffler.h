#pragma once
#include "internal_communication/filenames.h"
#include "internal_communication/read_tsv.h"
#include "util/filesystem.h"

#include <vector>
#include <string>
#include <fstream>

template<typename Key, typename Value, typename Hasher = std::hash<Key>>
class Shuffler {
  using KVList = std::vector<std::pair<Key, Value>>;
  using BucketsList = std::vector<KVList>;

 public:
  Shuffler(std::string output_dir, size_t reducer_number, int process_rank, Hasher hasher = Hasher())
    : output_dir_path_(std::move(output_dir))
    , reducer_number_(reducer_number)
    , process_rank_(process_rank)
    , hasher_(hasher) {
  }

  void Shuffle(const fs::path& mapper_file);

  BucketsList SplitToBuckets(const fs::path& mapper_file);

 private:
  fs::path output_dir_path_;
  size_t reducer_number_;
  int process_rank_;
  Hasher hasher_;
};

template<typename Key, typename Value, typename Hasher>
void Shuffler<Key, Value, Hasher>::Shuffle(const fs::path& mapper_file) {
  BucketsList buckets = SplitToBuckets(mapper_file);

  for (size_t i = 0; i < buckets.size(); ++i) {
    std::ofstream out_stream(output_dir_path_ / GetShufflerOutputFileName(i, process_rank_));
    for (auto& [key, value] : buckets[i]) {
      out_stream << key << '\t' << value << '\n';
    }
  }
}

template<typename Key, typename Value, typename Hasher>
typename Shuffler<Key, Value, Hasher>::BucketsList
Shuffler<Key, Value, Hasher>::SplitToBuckets(const fs::path& mapper_file) {
  BucketsList result(reducer_number_);

  KVList kv_list = ReadTSV<Key, Value>(mapper_file);
  for (auto& kv_pair : kv_list) {
    result[hasher_(kv_pair.first) % reducer_number_].emplace_back(std::move(kv_pair));
  }
  return result;
}
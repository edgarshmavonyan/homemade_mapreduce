#pragma once
#include "internal_communication/read_tsv.h"
#include "internal_communication/filenames.h"
#include "util/filesystem.h"

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

template<typename Key, typename Value>
class SortMerger {
 public:
  SortMerger(const std::string& dir_path, size_t reducer_id,
             int mapper_start_rank, size_t mapper_number)
      : dir_path_(dir_path)
      , reducer_id_(reducer_id)
      , mapper_start_rank_(mapper_start_rank)
      , mapper_number_(mapper_number) {
  }

  void MergeFilesAndSort();

 private:
  using KVList = std::vector<std::pair<Key, Value> >;
  using GroupedKV = std::vector<std::pair<Key, std::vector<Value>>>;

  static bool
  KeyComparator(const std::pair<Key, Value>& first, const std::pair<Key, Value>& other) {
    return first.first < other.first;
  }

 private:
  void CallSort(KVList& reducer_input);


  GroupedKV GroupByKey(KVList& sorted_input);

  void Write(const GroupedKV& grouped_kv);

 private:
  fs::path dir_path_;
  size_t reducer_id_;
  int mapper_start_rank_;
  size_t mapper_number_;
};

template<typename Key, typename Value>
void SortMerger<Key, Value>::MergeFilesAndSort() {
  KVList reducer_input;
  for (int rank = mapper_start_rank_;
       rank < mapper_start_rank_ + mapper_number_;
       ++rank) {

    std::ifstream stream(dir_path_ / GetShufflerOutputFileName(reducer_id_, rank));
    KVList cur_file_data = ReadTSV<Key, Value>(dir_path_ / GetShufflerOutputFileName(reducer_id_, rank));
    reducer_input.insert(reducer_input.end(), cur_file_data.begin(), cur_file_data.end());
  }

  CallSort(reducer_input);
  auto grouped = GroupByKey(reducer_input);
  Write(grouped);
}

template<typename Key, typename Value>
void SortMerger<Key, Value>::CallSort(KVList& reducer_input) {
  std::sort(reducer_input.begin(), reducer_input.end(), KeyComparator);
}

template<typename Key, typename Value>
typename SortMerger<Key, Value>::GroupedKV
SortMerger<Key, Value>::GroupByKey(KVList& sorted_input) {
  GroupedKV result;
  Key cur_key;
  for (size_t index = 0; index < sorted_input.size(); ++index) {
    if (index == 0 || sorted_input[index].first != cur_key) {
      result.emplace_back(sorted_input[index].first, std::vector<Value>());
    }
    result.back().second.push_back(sorted_input[index].second);
    cur_key = sorted_input[index].first;
  }
  return result;
}

template<typename Key, typename Value>
void SortMerger<Key, Value>::Write(const GroupedKV& grouped_kv) {
  std::ofstream out_stream(dir_path_ / GetReducerInputFileName(reducer_id_));
  for (auto& [key, values] : grouped_kv) {
    out_stream << key << '\t';
    for (size_t i = 0; i < values.size(); ++i) {
      out_stream << values[i];
      if (i + 1 != values.size()) {
        out_stream << '\t';
      }
    }
    out_stream << '\n';
  }
}

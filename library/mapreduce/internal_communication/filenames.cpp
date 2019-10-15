#include "filenames.h"

std::string GetShufflerOutputFileName(size_t reducer_id, int process_rank) {
    return std::to_string(reducer_id) + '_' + std::to_string(process_rank);
}

const std::string kReducerInputFileNamePrefix = "reduce_";

std::string GetReducerInputFileName(size_t reducer_id) {
  return kReducerInputFileNamePrefix + std::to_string(reducer_id);
}

const std::string kReducerOutputFileNamePrefix = "reduce_out_";

std::string GetReducerOutputFileName(size_t reducer_id) {
  return kReducerOutputFileNamePrefix + std::to_string(reducer_id);
}

const std::string kTempDirectoryName = "mr_temp_dir_";

std::string GetTempDirectory() {
  return kTempDirectoryName;
}

const std::string kMapperOutputFileNamePrefix = "maptemp_";

std::string GetMapperOutputFileName(int process_rank) {
  return kMapperOutputFileNamePrefix + std::to_string(process_rank);
}
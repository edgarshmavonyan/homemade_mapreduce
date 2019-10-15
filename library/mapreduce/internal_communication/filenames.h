#pragma once
#include <string>

std::string GetShufflerOutputFileName(size_t reducer_id, int process_rank);

std::string GetReducerInputFileName(size_t reducer_id);

std::string GetReducerOutputFileName(size_t reducer_id);

std::string GetTempDirectory();

std::string GetMapperOutputFileName(int process_rank);
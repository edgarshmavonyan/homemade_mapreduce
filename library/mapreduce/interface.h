#pragma once
#include "input_processing/process.h"
#include "internal_communication/input_sender.h"
#include "internal_communication/filenames.h"
#include "operations/mapper_interface.h"
#include "operations/reducer_interface.h"
#include "service_operations/shuffler.h"
#include "service_operations/sort_merger.h"
#include "util/argument_parser.h"

#include <string>

#include <mpi.h>


void MapReduceInit();

void MapReduceFinalize();

template<typename Key, typename Value>
fs::path RunMap(
    const std::string& input_path,
    const std::string& output_directory,
    MapperInterface<Key, Value>& mapper) {

  int world_size, rank;

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  fs::path output_file;

  if (rank == 0) {
    SlicedInput sliced_input = ProcessInput(input_path);
    InputSender input_sender(sliced_input, world_size - 1, 1);
    input_sender.Send();
  } else {
    InputReader input_reader(0);
    input_reader.Receive();
    OutputWriter<Key, Value> output_writer(output_directory, rank);

    mapper.Process(input_reader, output_writer);
    output_file = output_writer.GetFileName();
  }

  MPI_Barrier(MPI_COMM_WORLD);
  return output_file;
}

// TODO: divide logically
template<typename Key, typename Value, typename OutKey, typename OutValue>
void RunMapReduce(
    const std::string& input_path,
    const std::string& output_directory,
    size_t reducer_number,
    MapperInterface<Key, Value>& mapper,
    ReducerInterface<Key, Value, OutKey, OutValue>& reducer) {


  int world_size, rank;

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  fs::path temp_directory = GetTempDirectory();

  if (rank == 0) {
    std::error_code code;
    fs::remove_all(temp_directory, code);
    fs::create_directory(temp_directory);
  }
  MPI_Barrier(MPI_COMM_WORLD);

  fs::path map_output = RunMap(input_path, temp_directory, mapper);

  if (rank != 0) {
    Shuffler<Key, Value> shuffler(temp_directory, reducer_number, rank);
    shuffler.Shuffle(map_output);
  }
  MPI_Barrier(MPI_COMM_WORLD);

  if (rank != 0 && rank <= int(reducer_number)) {
    size_t reducer_id = rank - 1;
    SortMerger<Key, Value> sort_merger(temp_directory, reducer_id, 1, world_size - 1);
    sort_merger.MergeFilesAndSort();

    fs::path reducer_input_path = temp_directory / GetReducerInputFileName(reducer_id);
    std::ifstream stream(reducer_input_path);
    fs::path output_dir_path(output_directory);
    OutputWriter<Key, Value> reducer_output(output_dir_path / GetReducerOutputFileName(reducer_id));
    while (stream.good()) {
      ReducerInput<Key, Value> kv_input(stream);
      if (kv_input.IsValid()) {
        reducer.Process(kv_input, reducer_output);
      }
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);
}

template<typename Key, typename Value, typename OutKey, typename OutValue>
void RunMapReduce(
    int argc,
    char* argv[],
    MapperInterface<Key, Value>& mapper,
    ReducerInterface<Key, Value, OutKey, OutValue>& reducer) {
  auto [input_path, output_directory, reducer_number] = ParseArguments(argc, argv);
  RunMapReduce(input_path, output_directory, reducer_number, mapper, reducer);
}

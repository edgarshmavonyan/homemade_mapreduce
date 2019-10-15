#include "interface.h"

void MapReduceInit() {
  MPI_Init(NULL, NULL);
}

void MapReduceFinalize() {
  MPI_Finalize();
}

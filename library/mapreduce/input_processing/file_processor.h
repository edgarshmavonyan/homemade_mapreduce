#pragma once
#include "input_processor_interface.h"

#include <fstream>

class FileProcessor: public AbstractFixedSizeProcessor {
 public:
  explicit FileProcessor(std::string path, size_t slice_size);
  ~FileProcessor() override;

  const std::string& GetPath() const;
  SlicedInput Process() override;

 private:
  std::string path_;
};
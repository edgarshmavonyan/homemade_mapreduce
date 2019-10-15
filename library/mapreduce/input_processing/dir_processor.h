#pragma once
#include "input_processor_interface.h"

class DirProcessor: public AbstractFixedSizeProcessor {
 public:
  explicit DirProcessor(std::string path, size_t slice_size);
  ~DirProcessor() override;

  const std::string& GetDirPath() const;
  SlicedInput Process() override;


 private:
  std::string dir_path_;
};
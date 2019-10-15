#pragma once
#include "internal_communication/input_reader.h"
#include "internal_communication/output_writer.h"


template<typename Key, typename Value>
class MapperInterface {
 public:
  using Writer = OutputWriter<Key, Value>;
  using Reader = InputReader;

 public:
  virtual void Process(Reader& input_reader, Writer& output_writer) = 0;
};
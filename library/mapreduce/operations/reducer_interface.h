#pragma once
#include "internal_communication/reducer_input.h"
#include "internal_communication/output_writer.h"

template<typename Key, typename Value, typename OutKey = Key, typename OutValue = Value>
class ReducerInterface {
 public:
  using Reader = ReducerInput<Key, Value>;
  using Writer = OutputWriter<OutKey, OutValue>;

 public:
  virtual void Process(Reader& input_reader, Writer& output_writer) = 0;
};
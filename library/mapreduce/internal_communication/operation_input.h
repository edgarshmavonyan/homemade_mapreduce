#pragma once
#include <iostream>

template<typename InputType>
class OperationInputInterface {
 public:
  virtual ~OperationInputInterface() = 0;

  virtual void Next() = 0;

  virtual bool IsValid() const = 0;

  virtual const InputType& Get() const = 0;
};

template<typename InputType>
OperationInputInterface<InputType>::~OperationInputInterface() = default;

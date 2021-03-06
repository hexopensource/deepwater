/*!
 *  Copyright (c) 2016 by Contributors
 * \file executor.cxx
 * \brief implementation of the executor
 * \author Zhang Chen, Chuntao Hong
 */

#include <vector>
#include <set>
#include <map>
#include <string>
#include "executor.h"
#include "optimizer.h"

namespace mxnet {
namespace cpp {
Executor::Executor(const Symbol &symbol, Context context,
                   const std::vector<NDArray> &arg_arrays,
                   const std::vector<NDArray> &grad_arrays,
                   const std::vector<OpReqType> &grad_reqs,
                   const std::vector<NDArray> &aux_arrays) {
  this->symbol_ = symbol;
  this->arg_arrays = arg_arrays;
  this->grad_arrays = grad_arrays;
  this->aux_arrays = aux_arrays;

  std::vector<NDArrayHandle> arg_handles;
  std::vector<NDArrayHandle> grad_handles;
  std::vector<NDArrayHandle> aux_handles;

  for (const auto &array : arg_arrays) {
    arg_handles.push_back(array.GetHandle());
  }
  for (const auto &array : grad_arrays) {
    grad_handles.push_back(array.GetHandle());
  }
  for (const auto &array : aux_arrays) {
    aux_handles.push_back(array.GetHandle());
  }

  std::vector<mx_uint> grad_reqs_uint;
  for (auto s : grad_reqs) grad_reqs_uint.push_back(s);

  CHECK_EQ(MXExecutorBind(symbol.GetHandle(), context.GetDeviceType(),
                          context.GetDeviceId(), arg_handles.size(),
                          arg_handles.data(), grad_handles.data(),
                          grad_reqs_uint.data(), aux_handles.size(),
                          aux_handles.data(), &handle_),
           0);

  mx_uint out_size;
  NDArrayHandle *out_array;
  CHECK_EQ(MXExecutorOutputs(handle_, &out_size, &out_array), 0);
  for (mx_uint i = 0; i < out_size; ++i) {
    outputs.push_back(NDArray(out_array[i]));
  }
}

void Executor::UpdateAll(Optimizer *opt, float lr, float wd,
                         int arg_update_begin, int arg_update_end) {
  arg_update_end = arg_update_end < 0 ? arg_arrays.size() - 1 : arg_update_end;
  for (int i = arg_update_begin; i < arg_update_end; ++i) {
    opt->Update(i, arg_arrays[i], grad_arrays[i], lr, wd);
  }
}

std::map<std::string, NDArray> Executor::GetDict(const std::vector<std::string> &names,
                                                 const std::vector<NDArray> &arrays) {
  std::map<std::string, NDArray> ret;
  std::set<std::string> name_set;
  for (const auto &s : names) {
    CHECK_EQ(name_set.find(s), name_set.end()) << "Duplicate names detected, "
        << s;
    name_set.insert(s);
  }
  CHECK_EQ(name_set.size(), arrays.size())
      << "names size not equal to arrays size";
  for (size_t i = 0; i < names.size(); ++i) {
    ret[names[i]] = arrays[i];
  }
  return ret;
}
}  // namespace cpp
}  // namespace mxnet


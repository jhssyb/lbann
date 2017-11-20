////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2016, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory.
// Written by the LBANN Research Team (B. Van Essen, et al.) listed in
// the CONTRIBUTORS file. <lbann-dev@llnl.gov>
//
// LLNL-CODE-697807.
// All rights reserved.
//
// This file is part of LBANN: Livermore Big Artificial Neural Network
// Toolkit. For details, see http://software.llnl.gov/LBANN or
// https://github.com/LLNL/LBANN.
//
// Licensed under the Apache License, Version 2.0 (the "Licensee"); you
// may not use this file except in compliance with the License.  You may
// obtain a copy of the License at:
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied. See the License for the specific language governing
// permissions and limitations under the license.
//
// lbann_model_sequential .hpp .cpp - Sequential neural network models
////////////////////////////////////////////////////////////////////////////////

#ifndef LBANN_MODEL_SEQUENTIAL_HPP
#define LBANN_MODEL_SEQUENTIAL_HPP

#include "lbann/models/model.hpp"
#include "lbann/layers/layer.hpp"
#include "lbann/layers/activations/activation.hpp"
#include "lbann/data_readers/data_reader.hpp"
#include "lbann/io/persist.hpp"
#include <vector>
#include <string>

namespace lbann {

class sequential_model : public model {
 public:

  /** Constructor. */
  sequential_model(int max_mini_batch_size,
                   lbann_comm *comm,
                   objective_functions::objective_function *obj_fn,
                   optimizer_factory *optimizer_fac);
  
  /** Copy constructor. */
  sequential_model(const sequential_model& other) = default;

  /** Copy assignment operator. */
  sequential_model& operator=(const sequential_model& other) = default;

  /** Destructor. */
  ~sequential_model() override = default;

  /** Create copy. */
  sequential_model* copy() const override { return new sequential_model(*this); }

  /** Remove layer from sequential model. */
  void remove(int index);

  /** Insert layer in sequential model. */
  void insert(int index, Layer *new_layer);

  /** Replace layer in sequential model. */
  Layer *swap(int index, Layer *new_layer);

  /** Setup sequential model. */
  void setup() override;

  /** Get model name. */
  std::string name() const override { return "sequential_model"; }

  /** Setup subset of sequential model. */
  virtual void setup_subset(int start_index, int end_index);  

  /// returns the number of neurons in the most recently added layer, or -1
  /// if there is none
  int num_previous_neurons();

#if 0
  /// Save model to file
  /** @todo This is old and likely broken */
  bool save_to_file(const std::string file_dir);
  /// Load model from file
  /** @todo This is old and likely broken */
  bool load_from_file(const std::string file_dir);

  /// Save model to checkpoint
  /** @todo This is old and likely broken */
  bool save_to_checkpoint(int fd, const char *filename, size_t *bytes);
  /// Load model from checkpoint
  /** @todo This is old and likely broken */
  bool load_from_checkpoint(int fd, const char *filename, size_t *bytes);

  bool save_to_checkpoint_shared(persist& p) override;
  bool load_from_checkpoint_shared(persist& p) override;
#endif // 0

};

}  // namespace lbann

#endif  // LBANN_MODEL_SEQUENTIAL_HPP

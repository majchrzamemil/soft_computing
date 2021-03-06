#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>

#include "TrainingPattern.hpp"

class Neuron {
 public:
  //If weights would be big vector maybe unique_ptr and move not coppy
  Neuron(std::vector<double> weights);
  double calculateOutput(const TrainingPattern &trainingPattern);
  void updateWeights(const TrainingPattern &trainingPattern, const double trainingStep);
 
 private:
  std::vector<double> weights;
};

#endif

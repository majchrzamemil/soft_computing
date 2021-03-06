#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>

#include "TrainingPattern.hpp"

class Neuron {
 public:
  //If weights would be big vector maybe unique_ptr and move not coppy
  Neuron(std::vector<double> weights, bool bias);
 
  void calculateOutput(const TrainingPattern &trainingPattern);
 
  void updateWeights(const double trainingStep, const TrainingPattern &trainingPattern, bool isHidden);
 
  double activationFunction(); 
 
  void calculateError(const TrainingPattern &trainingPattern, const std::vector<Neuron> &upperLayer, unsigned int neuronNumber);
  double getOutput() {
    return output;
  };

  double getWeight(unsigned int index) const {
    return weights[index]; 
  }

  double getError() const {
    return error; 
  }

 private:
  std::vector<double> weights;
  //Just some big initial value
  double output {100};
  double error {0};
  bool bias;
};

#endif

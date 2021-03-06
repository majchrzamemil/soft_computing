#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>

#include "Neuron.hpp"
#include "TrainingPattern.hpp"

class Network {
 public:
  Network(std::vector<Neuron> &hiddenLayer, std::vector<Neuron> &outputLayer): hiddenLayer(hiddenLayer), outputLayer(outputLayer) {} ;
  void learn(const TrainingPattern &pattern, const double trainingStep);

 private:
  std::vector<Neuron> hiddenLayer;
  std::vector<Neuron> outputLayer;

};
#endif

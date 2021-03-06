#include "Neuron.hpp"

Neuron::Neuron(std::vector<double> weights) : weights(weights) {}

//Lets say that we are sure that vectors are the same size for now
double Neuron::calculateOutput(const TrainingPattern &trainingPattern) {
  double output {0};
  auto weight = weights.begin();
  auto vec = trainingPattern.getInputs();
  auto input = vec.begin();
  for (; weight != weights.end(); ++weight, ++input) {
    output += *weight * *input;
  }
  return output;
}


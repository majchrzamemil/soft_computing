#include "Neuron.hpp"

#include <iostream>
#include <math.h>

Neuron::Neuron(std::vector<double> weights, bool bias) : weights(weights), bias(bias) {}

//Lets say that we are sure that vectors are the same size for now
void Neuron::calculateOutput(const TrainingPattern &trainingPattern) {
  output  = 0;
  auto vec = trainingPattern.getInputs();
  auto input = vec.begin();
  for (unsigned int i {0}; i < vec.size(); ++i,  ++input) {
    output += weights[i] * *input;
  }
  if (bias) {
    output += weights.back();
  }
}

void Neuron::updateWeights(const double trainingStep, const TrainingPattern &trainingPattern, bool isHidden) {
  for (unsigned int i = 0; i < trainingPattern.getInputs().size(); ++i) {
    weights[i] += error * trainingStep * trainingPattern.getInputs()[i];
  }
  if (bias) {
    weights[weights.size()-1] +=error * trainingStep;
  }
}

double Neuron::activationFunction() {
  constexpr auto beta = 1;
  return 1 / (1 + exp(-(beta * output)));
}

void Neuron::calculateError(const TrainingPattern &pattern, const std::vector<Neuron> &upperLayer,
                            unsigned int neuronNumber) {
  if (upperLayer.size() == 0) {
    error = pattern.getExpectedOutput(neuronNumber) - activationFunction();
  } else {
    error = 0;
    for (unsigned int i{0}; i < upperLayer.size(); ++i) {
      auto &neuron = upperLayer[i];
      error += neuron.getWeight(neuronNumber) * neuron.getError();
    }
  }
  error *= activationFunction() * (1 - activationFunction());
  //rror *= exp(-output) / ((1 + exp(-output) * (1 + exp(-output))));
}


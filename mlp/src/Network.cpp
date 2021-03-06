#include "Network.hpp"
#include <iostream>
void Network::learn(const TrainingPattern &pattern, const double trainingStep) {
  std::vector<double> inputsForOutputLayer;
  for (auto hiddenNeuron = hiddenLayer.begin(); hiddenNeuron != hiddenLayer.end(); ++hiddenNeuron) {
    hiddenNeuron->calculateOutput(pattern);
    inputsForOutputLayer.push_back(hiddenNeuron->activationFunction());
    std::cout << "Hidden layer:" << hiddenNeuron->activationFunction() << "\n";
  }

  TrainingPattern hiddenPattern{inputsForOutputLayer, pattern.getExpectedOutputs()};

  for (auto outputNeuron = outputLayer.begin(); outputNeuron != outputLayer.end(); ++outputNeuron) {
    outputNeuron->calculateOutput(hiddenPattern);
    outputNeuron->activationFunction();
    std::cout << "Output Neuron no. : " << std::distance(outputLayer.begin(),
              outputNeuron) << ", Output: " << outputNeuron->activationFunction() << " Expected: " << pattern.getExpectedOutput(
                std::distance(outputLayer.begin(), outputNeuron)) << "\n";
    outputNeuron->calculateError(hiddenPattern, std::vector<Neuron> {}, std::distance(outputLayer.begin(), outputNeuron));

  }

  for (auto hiddenNeuron = hiddenLayer.begin(); hiddenNeuron != hiddenLayer.end(); ++hiddenNeuron) {
    hiddenNeuron->calculateError(pattern, outputLayer, std::distance(hiddenLayer.begin(), hiddenNeuron));
    hiddenNeuron->updateWeights(trainingStep, pattern, true);
  }
  for (auto outputNeuron = outputLayer.begin(); outputNeuron != outputLayer.end(); ++outputNeuron) {
    outputNeuron->updateWeights(trainingStep, hiddenPattern, false);
  }
  std::cout << "\n";
}


#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "Neuron.hpp"
#include "Network.hpp"
#include "Variables.hpp"
#include "TrainingPattern.hpp"

std::vector<double> generateWeights(const uint8_t numberOfInputs) {
  std::uniform_real_distribution<double> unif(LOWER_BOUND_WEIGHT, UPPER_BOUND_WEIGHT);
  std::default_random_engine re;
  //In proper solution there should be factory for creating Neurons

  std::vector<double> weights;
  for (uint8_t it = 0; it < numberOfInputs; ++it) {
    weights.push_back(unif(re));
  }
  return weights;
}

std::vector<TrainingPattern> readFile() {
  std::vector<TrainingPattern> patterns;
  std::ifstream ifs(FILE_PATH);

  boost::archive::xml_iarchive xmlIn(ifs);
  while (true) {
    TrainingPattern trainingPattern{};
    try {
      xmlIn >> boost::serialization::make_nvp("TrainingPattern", trainingPattern);
    } catch (boost::archive::archive_exception &e) {
      break;
    }
    patterns.push_back(trainingPattern);
  }
  return patterns;
}

int main() {
  std::vector<TrainingPattern> patterns = readFile();
  auto inputsSize = patterns[0].getInputs().size();
  const auto numberOfHiddenWeights = BIAS ? (inputsSize + 1) : inputsSize; 
  
  std::vector<Neuron> hiddenLayer;
  std::vector<Neuron> outputLayer;

  for (auto i = 0; i < NO_HIDDEN_NEURONS; ++i) {
    hiddenLayer.push_back(Neuron{generateWeights(numberOfHiddenWeights), BIAS}); 
  }

  const auto numberOfOutputWeights = BIAS ? (hiddenLayer.size() + 1) : hiddenLayer.size(); 

  for (unsigned int i = 0; i < inputsSize; ++i) {
    outputLayer.push_back(Neuron{generateWeights(numberOfOutputWeights), BIAS}); 
  }

  Network network {hiddenLayer, outputLayer};

  for (uint16_t it = 0; it < NUMBER_OF_ITERATIONS; ++it) {
    for (auto pattern = patterns.begin(); pattern != patterns.end(); ++pattern) {
        network.learn(*pattern, TRAINING_STEP);
    }

    std::cout << "Epoch: " << it << "\n";
    
    std::random_shuffle(patterns.begin(), patterns.end());
  }
  return 0;
}

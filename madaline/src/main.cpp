#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "Neuron.hpp"
#include "Variables.hpp"
#include "TrainingPattern.hpp"

std::vector<TrainingPattern> readFile(const std::string &fileName) {
  std::vector<TrainingPattern> trainingPatterns;
  std::ifstream ifs(fileName);

  boost::archive::xml_iarchive xmlIn(ifs);
  while (true) {
    TrainingPattern trainingPattern{};
    try {
      xmlIn >> boost::serialization::make_nvp("TrainingPattern", trainingPattern);
    } catch (boost::archive::archive_exception &e) {
      break;
    }
    trainingPatterns.push_back(trainingPattern);
  }
  ifs.close();
  return trainingPatterns;
}

int main() {
  std::vector<TrainingPattern> trainingPatterns = readFile(TRAINING_DATA);
  std::vector<TrainingPattern> patterns = readFile(DATA);
  // std::vector<std::shared_ptr<Neuron>> neurons;
  std::vector<Neuron> neurons;

  for (auto &pattern : trainingPatterns) {
    neurons.push_back(Neuron(pattern.getInputs()));
  }
  for (auto &pattern : patterns) {
    std::vector<double> outputs;
    for (auto neuron : neurons) {
      outputs.push_back(neuron.calculateOutput(pattern));
    }
    double maxOutput {0};
    uint8_t index {0};
    for (auto it = outputs.begin(); it != outputs.end(); ++it) {
      std::cout << *it <<"\n"; 
      if (*it > maxOutput) {
        maxOutput = *it;
        index = std::distance(outputs.begin(), it);
      }
    }

    std::cout << "Expected: " << pattern.getExpectedOutput() << ", Recognized: " <<
              trainingPatterns[index].getExpectedOutput() << ", accuracy: " << maxOutput << "\n";
  }

  return 0;
}

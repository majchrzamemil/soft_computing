#include "GeneticAlgorithm.hpp"

#include <cstring>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <iostream>
#include <algorithm>

GeneticAlgorithm::GeneticAlgorithm(uint8_t nrOfBits) : numberOfBits(nrOfBits) {}

double GeneticAlgorithm::fitnessFunction(double x) {
  return (std::exp(x) * std::sin(10 * x * std::acos(-1) * x) + 1) / x + 5;
}

Individual* GeneticAlgorithm::crossing(Individual *individual1, Individual *individual2) {
  const uint64_t bitPlaceToSwap = std::rand() % numberOfBits;
  uint64_t afterCrossing = 0;
  uint64_t individual1UChromosome = individual1->getUIntValue();
  uint64_t individual2UChromosome = individual2->getUIntValue();
  for (uint8_t it{0}; it < numberOfBits; ++it) {
    if (it < bitPlaceToSwap) {
      afterCrossing |= (((individual1UChromosome >> it) & 1UL) % 2UL) << it;
    } else {
      afterCrossing |= (((individual2UChromosome >> it) & 1UL) % 2UL) << it;
    }
  }
  Individual *output = new Individual{*individual1};
  output->setUIntValue(afterCrossing);
  return output;
}

Individual* GeneticAlgorithm::mutation(Individual *individual) {
  const uint64_t bitPlaceToSwap = std::rand() % numberOfBits;
  uint64_t afterMutation = individual->getUIntValue();
  afterMutation ^= 1UL << bitPlaceToSwap;
  Individual *output = new Individual{*individual};
  output->setUIntValue(afterMutation);
  return output;
}

Individual* GeneticAlgorithm::rullete(std::vector<Individual*> *individuals) {
  double overallFittness {0};
  for (auto individual : *individuals) {
    overallFittness += individual->getFitness();
  }
  for (auto individual : *individuals) {
    double p = individual->getFitness() / overallFittness;
    individual->setPropability(p);
  }
  
  std::sort(individuals->begin(), individuals->end(), [](Individual * individual1, Individual *individual2) {
    return individual1->getPropability() > individual2->getPropability();
  });

  std::vector<double> q;
  double tmpQ {0};
  for (uint64_t i {0}; i < individuals->size(); ++i) {
    for (uint64_t j {0}; j <= i; ++j) {
      tmpQ += individuals->at(j)->getPropability();
    }
    q.push_back(tmpQ);
    tmpQ = 0;
  }
  double r = ((double) rand() / (RAND_MAX));
  uint32_t index {0};
  for (auto i{0}; i < q.size(); ++i) {
    if (q[i] > r) {
      index = i;
      break;
    }
  }
  return (*individuals)[index];
}

#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <bitset>
#include <ctime>
#include <cstdlib>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "Variables.hpp"
#include "GeneticAlgorithm.hpp"
#include "Individual.hpp"

int calculateM(uint8_t precision) {
  int power = 0;
  double leftSide = (UPPER_BOUND - LOWER_BOUND) * std::pow(10, precision);
  double rightSide = std::pow(2, power) - 1;

  while (leftSide > rightSide) {
    ++power;
    rightSide = std::pow(2, power) - 1;
  }
  return power;
}

std::vector<Individual*> generateIndividuals(const uint8_t numberOfInputs) {
  const int nrOfBits = calculateM(PRECISION);
  std::vector<Individual*> indiciduals;
  uint64_t iValue = 0;
  for (uint8_t it = 0; it < numberOfInputs; ++it) {
    for (uint8_t bitNr = 0; bitNr < nrOfBits; ++bitNr) {
      iValue |= (unsigned long)std::rand() % 2 << bitNr;
    }
    indiciduals.push_back(new Individual{iValue, UPPER_BOUND, LOWER_BOUND, nrOfBits});
    iValue = 0;
  }
  return indiciduals;
}


int main() {
  std::srand(std::time(nullptr));
  GeneticAlgorithm geneticAlgorithm(calculateM(PRECISION));
  std::vector<Individual*> individuals = generateIndividuals(POPULATION_SIZE);
  for (auto individual : individuals) {
    individual->setFitness(geneticAlgorithm.fitnessFunction(individual->getDoubleValue()));
  }

  geneticAlgorithm.rullete(&individuals);
  for (uint32_t it {0}; it < NUMER_OF_GENERATIONS ; ++it) {
    double avrageFittnes {0};
    for (auto individual : individuals) {
      individual->setFitness(geneticAlgorithm.fitnessFunction(individual->getDoubleValue()));
      avrageFittnes += individual->getFitness();
    }
    avrageFittnes /= individuals.size();
    if (avrageFittnes < MAX_FF_DELTA) {
      break;
    }

    double r = ((double) rand() / (RAND_MAX));
    if (r < MUTATION_PROPABILITY) {
      Individual *individual = geneticAlgorithm.rullete(&individuals);
      Individual *afterMutation = geneticAlgorithm.mutation(individual);
      delete individuals[0];
      individuals[0] = afterMutation;
    } else if (r <= CROSS_PROPABILITY) {

      Individual *individual1 = geneticAlgorithm.rullete(&individuals);
      Individual *individual2 = geneticAlgorithm.rullete(&individuals);
      while (individual1->getDoubleValue() == individual2->getDoubleValue()) {
        individual2 = geneticAlgorithm.rullete(&individuals);
      }
      Individual *afterCrossing = geneticAlgorithm.crossing(individual1, individual2);
      delete individuals[0];
      delete individuals[1];
      Individual *individual = new Individual{*afterCrossing};
      individuals[0] = afterCrossing;
      individuals[1] = individual;
    } else {
      Individual *individual = geneticAlgorithm.rullete(&individuals);
      if (individual->getDoubleValue() != individuals[0]->getDoubleValue()) {
        delete individuals[0];
      }
      individuals[0] = new Individual{*individual};
    }
  }
  std::cout << individuals[individuals.size() - 1]->getDoubleValue() << std::endl;
  for (auto individual : individuals) {
    delete individual;
  }
  return 0;
}

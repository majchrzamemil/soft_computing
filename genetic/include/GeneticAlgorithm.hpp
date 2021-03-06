#include "Individual.hpp"
#include <vector>

class GeneticAlgorithm {
 public:
  GeneticAlgorithm(uint8_t nrOfBits);
  double fitnessFunction(double x);
  Individual* crossing(Individual *individual1, Individual *individual2);
  Individual* mutation(Individual *individual);
  Individual* rullete(std::vector<Individual*> *individuals);
 private:
  const  uint8_t numberOfBits;
};

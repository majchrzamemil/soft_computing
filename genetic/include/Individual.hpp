#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP
#include <cstdint>

class Individual {
 public:
  Individual(double geneD, double upperBound, double lowerBound, int po);

  Individual(uint64_t geneI, double upperBound, double lowerBound, int po);


  Individual(const Individual&) = default;
  double getDoubleValue() {
    calculateX();    
    return dValue;
  }

  uint64_t getUIntValue() {
    return iValue;
  }

  double getFitness() {
    return fitness;
  }

  double getPropability() {
    return propability; 
  }

  void setPropability(double p) {
    propability = p; 
  }
  void setUIntValue(uint64_t value);
  void setFitness(double fitnessV);
 private:
  void calculateX();
  const double upperBound;
  const double lowerBound;
  double dValue;
  uint64_t iValue;
  int p;
  double fitness;
  double propability;
};
#endif

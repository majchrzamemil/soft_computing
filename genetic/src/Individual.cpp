
#include "Individual.hpp"
#include <iostream>
#include <cmath>

Individual::Individual(double geneD, double upperBound, double lowerBound, int po): upperBound(upperBound),
  lowerBound(lowerBound), p(po) {
  dValue = geneD;
}

Individual::Individual(uint64_t geneI, double upperBound, double lowerBound, int po): upperBound(upperBound),
  lowerBound(lowerBound), p(po) {
  iValue = geneI;
}

void Individual::setUIntValue(uint64_t value) {
  iValue = value;
}

void Individual::setFitness(double fitnessV) {
  fitness = fitnessV;
}

void Individual::calculateX() {
  dValue = lowerBound + iValue * (upperBound - lowerBound) / (std::pow(2, p) - 1);
}

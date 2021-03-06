#include "TrainingPattern.hpp"

#include <cmath>

void TrainingPattern::normalize() {
  uint8_t normalizeCounter {0};
  for (auto &it : inputs) {
    if(it == 1) {
      ++normalizeCounter;
    }
  }
  for (auto it = inputs.begin(); it != inputs.end(); ++it) {
    *it = *it/std::sqrt(normalizeCounter); 
  }
}

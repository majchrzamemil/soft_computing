#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <cstdint>

constexpr double MAX_FF_DELTA {0.0001};
constexpr double LOWER_BOUND {0.5};
constexpr double UPPER_BOUND {2.5};
constexpr uint8_t PRECISION {3};
constexpr uint8_t POPULATION_SIZE {100};
constexpr uint32_t NUMER_OF_GENERATIONS {200};
constexpr double MUTATION_PROPABILITY {0.3};      // mutation probability
constexpr double CROSS_PROPABILITY {0.09};
constexpr double REPRODUCTION_PROPABILITY {1 - MUTATION_PROPABILITY -  CROSS_PROPABILITY};
#endif

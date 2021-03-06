#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <cstdint>

constexpr uint16_t NUMBER_OF_ITERATIONS {10000};
constexpr double MAX_ERROR {0.003};
constexpr double TRAINING_STEP {0.5};
constexpr double LOWER_BOUND_WEIGHT {-0.5};
constexpr double UPPER_BOUND_WEIGHT {0.5};
constexpr char FILE_PATH[] {"training_data.xml"};
constexpr uint8_t NO_HIDDEN_NEURONS {2};
constexpr bool BIAS {true};
#endif

#ifndef TRAINING_PATTERN_HPP
#define TRAINING_PATTERN_HPP
#include <vector>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/base_object.hpp> 
class TrainingPattern {
 public:

  template<class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    if (Archive::is_loading::value) {
      ar & boost::serialization::make_nvp("size", size); 
      for (unsigned int i = 0; i < size; i++) {
        double input;
        ar & boost::serialization::make_nvp("input", input); 
        inputs.push_back(input);
      }
      for (unsigned int i = 0; i < size; i++) {
        double output;
        ar & boost::serialization::make_nvp("output", output); 
        expectedOutputs.push_back(output);
      }
    }
  }
  TrainingPattern(std::vector<double> inputs, const std::vector<double> expectedOutputs) : inputs(inputs),
    expectedOutputs(expectedOutputs), size(0) {}
  TrainingPattern() {};

  double getExpectedOutput(unsigned int index) const {
    return expectedOutputs[index];
  }

  std::vector<double> getExpectedOutputs() const {
    return expectedOutputs;
  }

  void setExpectedOutput(const std::vector<double> expectedOutputs) {
    this->expectedOutputs = expectedOutputs;
  }

  void setInputs(const std::vector<double> inputs) {
    this->inputs = inputs;
  }

  std::vector<double> getInputs() const {
    return inputs;
  }

 private:
  friend class boost::serialization::access;
  std::vector<double> inputs;
  std::vector<double> expectedOutputs;
  unsigned int size;
};
#endif

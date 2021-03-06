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
      ar & boost::serialization::make_nvp("expectedOutput", expectedOutput);
      for (unsigned int i = 0; i < size; i++) {
        double input;
        ar & boost::serialization::make_nvp("input", input); 
        inputs.push_back(input);
      }
      normalize();
    } else {
      size = inputs.size();
      ar & boost::serialization::make_nvp("size",size);
      ar & boost::serialization::make_nvp("expectedOutput", expectedOutput);
      for (unsigned int i = 0; i < size; i++) {
        ar & boost::serialization::make_nvp("input", inputs[i]);
      }
    }
  }
  TrainingPattern(std::vector<double> inputs, const std::string expectedOutput) : inputs(inputs),
    expectedOutput(expectedOutput), size(0) {}
  TrainingPattern() {};

  std::string getExpectedOutput() const {
    return expectedOutput;
  }

  void setExpectedOutput(const std::string expectedOutput) {
    this->expectedOutput = expectedOutput;
  }

  void setInputs(const std::vector<double> inputs) {
    this->inputs = inputs;
  }

  std::vector<double> getInputs() const {
    return inputs;
  }

 private:
  void normalize();
  friend class boost::serialization::access;
  std::vector<double> inputs;
  std::string expectedOutput;
  unsigned int size;
};
#endif

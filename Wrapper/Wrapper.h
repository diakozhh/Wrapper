#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <iostream>


/**
 * @brief Wrapper class
 * Main class-wrapper over other class method
 */
class wrapper {
private:
  /**
  * @brief Pair of two vectors of arguments and name
  */
  std::pair<std::vector<std::string>, std::vector<int>> argM;
  /**
  * @brief Variable to store method function
  */
  std::function<int(std::vector<int>& argV)> function;
  /**
  * @brief Default constructor
  */
  wrapper() {};

  template<typename Subject, typename func, size_t... index>
  /**
  * @brief Method to call class method
  * @param subject is ptr to class
  * @param method is method of subject
  * @param argV is argument vector
  * @param std::index_sequence<index...> is sequence of integers to know indexes of arguments
  * @return result of methods
  */

  static int callMethod(Subject* subject, func method, const std::vector<int> argV, std::index_sequence<index...>) {
    return (subject->*method)(argV[index]...);
  }


public:
  template<typename subj, typename... args>
  /**
  * @brief Wrapper constructor
  * @param subj is pointer to class
  * @param int (subj::* subjMethod)(args...) is pointer to subject's methods
  * @warning Invalid count of arguments
  * @param _argM is argument's map with values and names
  */
  wrapper(subj* _subj, int (subj::* subjMethod)(args...), const std::map<std::string, int>& _argM) noexcept {
    if (_subj == nullptr || subjMethod == nullptr)
      return;

    for (auto& elem : _argM) {
      this->argM.first.push_back(elem.first);
      this->argM.second.push_back(elem.second);
    }
    function = [_subj, subjMethod](const std::vector<int>& argV) {
      if (sizeof...(args) != argV.size())
        throw std::exception("ERROR: invalid count of arguments");
      return callMethod(_subj, subjMethod, argV, std::make_index_sequence<sizeof...(args)>{});
    };
  }

  /**
  * @brief Executor command in wrapper
  * @param _argM is argements map
  * @return result is result of command
  * @warning Invalid arguments
  * @warning Uknown arguments
  */
  int execute(const std::map<std::string, int>& _argM) {
    std::vector<int> argV;

    if (this->argM.first.size() != _argM.size())
      throw std::exception("ERROR: invalid arguments");

    for (auto& elem : this->argM.first) {
      auto arg = _argM.find(elem);

      if (arg == _argM.end())
        throw std::exception("ERROR: unknown arguments");

      argV.push_back(arg->second);
    }
    int result;
    try {
      result = function(argV);
    }
    catch (std::exception& e) {
      throw e;
    }
    return result;
  }
  /**
  * @brief Wrapper destructor
  */
  ~wrapper() {};
};
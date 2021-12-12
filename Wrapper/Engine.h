#include "Wrapper.h"

#pragma once

/**
* @brief Engine class
* Executes methods of classes
*/

class engine {
private:
  std::map<std::string, wrapper*> _command;
public:
  /**
  * @brief Default engine constructor
  */
  engine() {};
  /**
  * @brief Register command in engine
  * @param name is command name
  * @param _wrapper is wrapper ptr
  */
  void command(const std::string& name, wrapper* _wrapper) {
    if (_wrapper == nullptr)
      return;
    if (_command.find(name) != _command.end())
      return;
    _command[name] = _wrapper;
  }
  /**
  * @brief Executor in engine
  * @param name is command name
  * @param args is argument map
  * @warning Invalid command
  * @return result is executor result
  */
  int execute(const std::string& name, const std::map<std::string, int>& args) {
    auto argName = _command.find(name);
    if (argName == _command.end())
      throw std::exception("ERROR: invalid command");
    int result;
    try {
      result = argName->second->execute(args);
    }
    catch (std::exception& e) {
      throw e;
    }
    return result;
  }
  /**
  * @brief Default engine destructor
  */
  ~engine() {};
};
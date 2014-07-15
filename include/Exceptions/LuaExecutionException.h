//
//  LuaExecutionException.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_LuaExecutionException_h
#define SpaceStationKeeper_LuaExecutionException_h

#include <stdexcept>

namespace BlazeEngine {
namespace Exceptions {

class LuaExecutionException : public runtime_error {
public:
  LuaExecutionException(string message)
      : runtime_error("An error occurred executing a LUA script: " + message) {}
  ~LuaExecutionException() {};
};
}
}

#endif

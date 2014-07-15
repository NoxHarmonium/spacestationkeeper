//
//  LuaDebug.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#include "LuaDebug.h"

namespace BlazeEngine {
namespace Binding {

using namespace std;

void LuaDebug::Log(const std::string &message) {
  cout << "[LUA] " << message << endl;
}
}
}

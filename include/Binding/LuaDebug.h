//
//  LuaDebug.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_LuaDebug_h
#define SpaceStationKeeper_LuaDebug_h

#include <string>
#include <iostream>

class LuaDebug {
public:
  static void Log(const std::string &message);
};

#endif

//
//  LuaBind.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#ifndef SpaceStationKeeper_LuaBind_h
#define SpaceStationKeeper_LuaBind_h

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// Attempt to fix luabind conflict with mactypes.h
#undef nil

#include <luabind/luabind.hpp>

#endif

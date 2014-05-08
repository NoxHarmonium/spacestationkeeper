//
//  ClassBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_ClassBinder_h
#define SpaceStationKeeper_ClassBinder_h

#include "LuaBindDeps.h"

// Specialise this template to create binders

template <typename... T> struct ClassBinder {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<T...>(name)];
  }
};

#endif

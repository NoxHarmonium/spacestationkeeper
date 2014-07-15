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
#include <stdexcept>

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {
// Specialise this template to create binders

template <typename... T> struct ClassBinder {
  static void Bind(const char *name, lua_State *L) {
    throw runtime_error("You need to specialise this class!");
    // luabind::module(L)[luabind::class_<T...>(name)];
  }
};
}
}
}

#endif

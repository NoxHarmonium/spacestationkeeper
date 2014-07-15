//
//  LuaDebugBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_LuaDebugBinder_h
#define SpaceStationKeeper_LuaDebugBinder_h

#include "ClassBinder.h"
#include "LuaDebug.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

template <> struct ClassBinder<LuaDebug> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<LuaDebug>(name)
                           .def(luabind::constructor<>())
                           .scope[luabind::def("Log", &LuaDebug::Log)]];
  }
};
}
}
}

#endif

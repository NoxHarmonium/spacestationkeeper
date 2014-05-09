//
//  CinderQuatBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_CinderQuatBinders_h
#define SpaceStationKeeper_CinderQuatBinders_h

#include "ClassBinder.h"

template <typename T> struct ClassBinder<Quaternion<T>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<Vec4<T>>(name)
                           .def(luabind::constructor<T, T, T, T>())];

    // TODO: LOTS OF THINGS
  }
};

#endif

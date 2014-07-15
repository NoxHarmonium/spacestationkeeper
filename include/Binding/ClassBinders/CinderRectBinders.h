//
//  CinderRectBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 9/05/2014.
//
//

#ifndef SpaceStationKeeper_CinderRectBinders_h
#define SpaceStationKeeper_CinderRectBinders_h

#include "ClassBinder.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

template <typename T> struct ClassBinder<RectT<T>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<RectT<T>>(name)
                           .def(luabind::constructor<T, T, T, T>())];
    // TODO All the methods and stuff
  }
};
}
}
}

#endif

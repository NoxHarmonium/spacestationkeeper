//
//  UtilsBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 10/05/2014.
//
//

#ifndef SpaceStationKeeper_UtilsBinder_h
#define SpaceStationKeeper_UtilsBinder_h

#include "ClassBinder.h"
#include "Utils.h"

template <> struct ClassBinder<Utils> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Utils>(name).def(luabind::constructor<>()).scope[
      luabind::def("isInside", (bool (*)(ci::AxisAlignedBox3f, ci::Vec2f)) &
                                   Utils::isInside),
      luabind::def("isInside", (bool (*)(ci::AxisAlignedBox3f, ci::Vec3f)) &
                                   Utils::isInside),
      luabind::def("areOverlapping", &Utils::areOverlapping)
    ]];

    // MORE!
  }
};

#endif

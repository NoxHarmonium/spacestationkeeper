//
//  EnumHelperBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 10/05/2014.
//
//

#ifndef SpaceStationKeeper_EnumHelperBinder_h
#define SpaceStationKeeper_EnumHelperBinder_h

#include "ClassBinder.h"
#include "EnumHelper.h"

template <> struct ClassBinder<EnumHelper> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<EnumHelper>(name)
               .def(luabind::constructor<>())
               .def(luabind::constructor<int>())
               .def("setFlag", &EnumHelper::setFlag)
               .def("clearFlag", &EnumHelper::clearFlag)
               .def("hasFlag", &EnumHelper::hasFlag)
               .def("getInternalValue", &EnumHelper::getInternalValue)];
    // TODO All the methods and stuff
  }
};

template <> struct ClassBinder<Passibility> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Passibility, EnumHelper>(name)
               .def(luabind::constructor<>())
               .def(luabind::constructor<int>())
               .def("setFlag", &EnumHelper::setFlag)
               .def("clearFlag", &EnumHelper::clearFlag)
               .def("hasFlag", &EnumHelper::hasFlag)
               .def("getInternalValue", &EnumHelper::getInternalValue)
               .enum_("constants")[
                 value("None", 0),
                 value("North", 1 << 0),
                 value("South", 1 << 1),
                 value("East", 1 << 2),
                 value("West", 1 << 3),
                 value("Unused", 1 << 4)
               ]];
    // TODO All the methods and stuff
  }
};

#endif

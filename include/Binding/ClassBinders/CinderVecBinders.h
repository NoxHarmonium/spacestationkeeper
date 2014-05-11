//
//  CinderVecBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_CinderVecBinders_h
#define SpaceStationKeeper_CinderVecBinders_h

#include "ClassBinder.h"
#include "luabind/operator.hpp"

template <typename T> struct ClassBinder<Vec2<T>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<Vec2<T>>(name)
                           .def(luabind::constructor<T, T>())
                           .def_readwrite("x", &Vec2<T>::x)
                           .def_readwrite("y", &Vec2<T>::y)
                           .def("limit", &Vec2<T>::limit)
                           // Operators
                           .def(self + Vec2<T>())
                           .def(self - Vec2<T>())
                           .def(self * T())
                           .def(self / T())
                           .def(self / Vec2<T>())
                           .def(self == Vec2<T>())
                           .def(tostring(self))];
  }
};

template <typename T> struct ClassBinder<Vec3<T>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<Vec3<T>>(name)
                           .def(luabind::constructor<T, T, T>())
                           .def_readwrite("x", &Vec3<T>::x)
                           .def_readwrite("y", &Vec3<T>::y)
                           .def_readwrite("z", &Vec3<T>::z)
                           .def("limit", &Vec2<T>::limit)
                           // Operators
                           .def(self + Vec3<T>())
                           .def(self - Vec3<T>())
                           .def(self * T())
                           .def(self / T())
                           .def(self / Vec3<T>())
                           .def(self == Vec3<T>())
                           .def(tostring(self))];
  }
};

template <typename T> struct ClassBinder<Vec4<T>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<Vec4<T>>(name)
                           .def(luabind::constructor<T, T, T, T>())
                           .def_readwrite("w", &Vec4<T>::x)
                           .def_readwrite("x", &Vec4<T>::y)
                           .def_readwrite("y", &Vec4<T>::y)
                           .def_readwrite("x", &Vec4<T>::y)
                           .def("limit", &Vec4<T>::limit)
                           // Operators
                           .def(self + Vec4<T>())
                           .def(self - Vec4<T>())
                           .def(self * T())
                           .def(self / T())
                           .def(self / Vec4<T>())
                           .def(self == Vec4<T>())
                           .def(tostring(self))];
  }
};

#endif

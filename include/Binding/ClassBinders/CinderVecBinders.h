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
                           .def("length", &Vec2<T>::length)
                           .def("normalize", &Vec2<T>::normalize)
                           .def("distance", &Vec2<T>::distance)
                           .def("rotate", &Vec2<T>::rotate)
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
                           .def("limit", &Vec3<T>::limit)
                           .def("normalize", &Vec3<T>::normalize)
                           .def("distance", &Vec3<T>::distance)
                           .def("rotate", &Vec3<T>::rotate)
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
                           .def_readwrite("w", &Vec4<T>::w)
                           .def_readwrite("x", &Vec4<T>::x)
                           .def_readwrite("y", &Vec4<T>::y)
                           .def_readwrite("z", &Vec4<T>::z)
                           .def("limit", &Vec4<T>::limit)
                           .def("normalize", &Vec4<T>::normalize)
                           .def("distance", &Vec4<T>::distance)
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

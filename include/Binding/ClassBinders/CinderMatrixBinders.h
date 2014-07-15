//
//  CinderMatrixBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_CinderMatrixBinders_h
#define SpaceStationKeeper_CinderMatrixBinders_h

#include "ClassBinder.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

template <typename T> struct ClassBinder<Matrix44<T>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)
        [luabind::class_<Matrix44<T>>(name)
             .def(luabind::constructor<>())
             .def_readwrite("transformPoint", &Matrix44<T>::transformPoint)
             .def_readwrite("transformPointAffine",
                            &Matrix44<T>::transformPointAffine)
             .def_readwrite("translate",
                            (void (Matrix44<T>::*)(const Vec3<T> &)) &
                                Matrix44<T>::translate)
             .def_readwrite("rotate", (void (Matrix44<T>::*)(const Vec3<T> &)) &
                                          Matrix44<T>::rotate)
             .def_readwrite("scale", (void (Matrix44<T>::*)(const Vec3<T> &)) &
                                         Matrix44<T>::scale)
             .def(self * other<Vec3<T>>())
             .def(self * T())];
    // TODO: Operators? More methods?
    // Vec 4 overloads?
  }
};

template <typename T> struct ClassBinder<Matrix33<T>> {

  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Matrix33<T>>(name).def(luabind::constructor<>())];
    // TODO: Operators? More methods?
  }
};

template <typename T> struct ClassBinder<Matrix22<T>> {

  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Matrix22<T>>(name).def(luabind::constructor<>())];
    // TODO: Operators? More methods?
  }
};
}
}
}

#endif

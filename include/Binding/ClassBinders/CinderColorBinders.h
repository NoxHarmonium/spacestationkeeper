//
//  CinderColorBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_CinderColorBinders_h
#define SpaceStationKeeper_CinderColorBinders_h

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

template <typename T> struct ClassBinder<ColorT<T>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<ColorT<T>>(name)
                           .def(luabind::constructor<T, T, T>())
                           .def_readwrite("r", &ColorT<T>::r)
                           .def_readwrite("g", &ColorT<T>::g)
                           .def_readwrite("b", &ColorT<T>::b)];

    // TODO: Operators?
  }
};

template <typename T> struct ClassBinder<ColorAT<T>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<ColorAT<T>>(name)
                           .def(luabind::constructor<T, T, T, T>())
                           .def_readwrite("r", &ColorAT<T>::r)
                           .def_readwrite("g", &ColorAT<T>::g)
                           .def_readwrite("b", &ColorAT<T>::b)
                           .def_readwrite("a", &ColorAT<T>::a)];

    // TODO: Operators?
  }
};
}
}
}

#endif

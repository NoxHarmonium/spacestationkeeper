
//
//  GameObjectBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_GameObjectBinder_h
#define SpaceStationKeeper_GameObjectBinder_h

#include "ClassBinder.h"
#include "GameObject.h"

template <> struct ClassBinder<GameObject> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<GameObject>(name)
                           .def(luabind::constructor<>())
                           .def("addComponent", &GameObject::addComponent)
                           .def("removeComponent", &GameObject::removeComponent)
                           .def("getRenderer", &GameObject::getRenderer)];
  }
};

#endif

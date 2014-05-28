
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
#include <luabind/iterator_ptr_policy.hpp>

using namespace luabind;

template <> struct ClassBinder<GameObject> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<GameObject, GameObjectRef>(name)
               .def(luabind::constructor<>())
               .def_readonly("renderer", &GameObject::renderer)
               .def("addComponent", &GameObject::addComponent)
               .def("removeComponent", &GameObject::removeComponent)
               .def("getComponent", &GameObject::getComponent)
               .def("reassignId", &GameObject::reassignId)
               .def("refreshComponentList", &GameObject::refreshComponentList)
               .def("getId", &GameObject::getId)
               .def("setId", &GameObject::setId)
               .def("getComponentList", &GameObject::getComponentList,
                    return_stl_iterator)
           //.def("getRenderer", &GameOb\ject::getRenderer)]; // Depricated for
           // nicer
           // looking code
    ];
  }
};

#endif

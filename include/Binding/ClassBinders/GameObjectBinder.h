
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
#include <luabind/adopt_policy.hpp>

using namespace luabind;

template <> struct ClassBinder<GameObject> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)
        [luabind::class_<GameObject>(name)
             .def(luabind::constructor<>())
             .def_readonly("renderer", &GameObject::renderer)
             .def("addComponent", &GameObject::addComponent,
                  luabind::detail::policy_cons<luabind::detail::adopt_policy<2>,
                                               luabind::detail::null_type>())
             .def("removeComponent", &GameObject::removeComponent)
         //.def("getRenderer", &GameObject::getRenderer)]; // Depricated for
         //nicer
         // looking code
    ];
  }
};

#endif

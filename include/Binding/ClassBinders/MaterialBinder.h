//
//  MaterialBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_MaterialBinder_h
#define SpaceStationKeeper_MaterialBinder_h

#include "ClassBinder.h"
#include "luabind/operator.hpp"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

using namespace luabind;

namespace Components = BlazeEngine::Components;

template <> struct ClassBinder<Components::Material> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Components::Material, Components::MaterialRef>(name)
               .def(constructor<>())
               .def_readwrite("texture", &Components::Material::texture)
               .def_readwrite("shader", &Components::Material::shader)
               .def_readwrite("brightness", &Components::Material::brightness)
               .def_readwrite("baseColor", &Components::Material::baseColor)
               .def(const_self == const_self)];
  }
};
}
}
}

#endif

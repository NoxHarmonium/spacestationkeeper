//
//  MaterialBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_MaterialBinder_h
#define SpaceStationKeeper_MaterialBinder_h

template <> struct ClassBinder<Material> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<Material, MaterialRef>(name)
                           .def(constructor<>())
                           .def_readwrite("texture", &Material::texture)
                           .def_readwrite("shader", &Material::shader)
                           .def_readwrite("brightness", &Material::brightness)
                           .def_readwrite("baseColor", &Material::baseColor)];
  }
};

#endif

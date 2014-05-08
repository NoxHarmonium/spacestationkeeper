//
//  BashMeshBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_BashMeshBinder_h
#define SpaceStationKeeper_BashMeshBinder_h

#include "ClassBinder.h"
#include "BaseMesh.h"

template <> struct ClassBinder<BaseMesh> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<BaseMesh, BaseMeshRef>(name)
               .def("getBoundingBox", (AxisAlignedBox3f (BaseMesh::*)(void)) &
                                          BaseMesh::getBoundingBox)
               .def("getBoundingBox",
                    (AxisAlignedBox3f (BaseMesh::*)(Matrix44f)) &
                        BaseMesh::getBoundingBox)];
  }
};

#endif

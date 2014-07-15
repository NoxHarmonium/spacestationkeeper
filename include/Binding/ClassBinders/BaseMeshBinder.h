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

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

namespace Components = BlazeEngine::Components;

template <> struct ClassBinder<Components::BaseMesh> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Components::BaseMesh, Components::BaseMeshRef>(name)
               .def("getBoundingBox",
                    (AxisAlignedBox3f (Components::BaseMesh::*)(void)) &
                        Components::BaseMesh::getBoundingBox)
               .def("getBoundingBox",
                    (AxisAlignedBox3f (Components::BaseMesh::*)(Matrix44f)) &
                        Components::BaseMesh::getBoundingBox)];
  }
};
}
}
}

#endif

//
//  BatchedMeshBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 10/05/2014.
//
//

#ifndef SpaceStationKeeper_BatchedMeshBinder_h
#define SpaceStationKeeper_BatchedMeshBinder_h

#include "ClassBinder.h"
#include "BatchedMesh.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

namespace Components = BlazeEngine::Components;

template <> struct ClassBinder<BatchedMesh> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)
        [luabind::class_<BatchedMesh, Components::BaseMesh, BatchedMeshRef>(
             name)
             .def(constructor<>())
             .def("getBoundingBox", (AxisAlignedBox3f (BatchedMesh::*)(void)) &
                                        BatchedMesh::getBoundingBox)
             .def("getBoundingBox",
                  (AxisAlignedBox3f (BatchedMesh::*)(Matrix44f)) &
                      BatchedMesh::getBoundingBox)
             .def("addMesh", &BatchedMesh::addMesh)];
  }
};
}
}
}

#endif

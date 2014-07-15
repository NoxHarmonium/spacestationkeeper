//
//  SimpleMeshBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 9/05/2014.
//
//

#ifndef SpaceStationKeeper_SimpleMeshBinder_h
#define SpaceStationKeeper_SimpleMeshBinder_h

#include "ClassBinder.h"
#include "SimpleMesh.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

namespace Components = BlazeEngine::Components;

template <> struct ClassBinder<SimpleMesh> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)
        [luabind::class_<SimpleMesh, Components::BaseMesh, SimpleMeshRef>(name)
             .def("getBoundingBox", (AxisAlignedBox3f (SimpleMesh::*)(void)) &
                                        SimpleMesh::getBoundingBox)
             .def("getBoundingBox",
                  (AxisAlignedBox3f (SimpleMesh::*)(Matrix44f)) &
                      SimpleMesh::getBoundingBox)
             .scope[def("generateQuad", &SimpleMesh::generateQuad)]];
  }
};
}
}
}

#endif

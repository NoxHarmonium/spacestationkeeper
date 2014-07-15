//
//  TransformBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_TransformBinder_h
#define SpaceStationKeeper_TransformBinder_h

#include "ClassBinder.h"
#include "Transform.h"
#include "FixStdSharedPtrBind.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

namespace Components = BlazeEngine::Components;

template <> struct ClassBinder<Components::Transform> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)
        [luabind::class_<Components::Transform, Components::TransformRef>(name)
             .def(luabind::constructor<>())
             .def("getTransformMatrixLocal",
                  &Components::Transform::getTransformMatrixLocal)
             .def("getTransformMatrixWorld",
                  &Components::Transform::getTransformMatrixWorld)
             .def_readwrite("localPosition",
                            &Components::Transform::localPosition)
             .def_readwrite("localRotation",
                            &Components::Transform::localRotation)
             .def_readwrite("localScale", &Components::Transform::localScale)
             .def_readwrite("parent", &Components::Transform::parent)];
  }
};
}
}
}

#endif

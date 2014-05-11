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

template <> struct ClassBinder<Transform> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Transform, TransformRef>(name)
               .def(luabind::constructor<>())
               .def("getTransformMatrixLocal",
                    &Transform::getTransformMatrixLocal)
               .def("getTransformMatrixWorld",
                    &Transform::getTransformMatrixWorld)
               .def_readwrite("localPosition", &Transform::localPosition)
               .def_readwrite("localRotation", &Transform::localPosition)
               .def_readwrite("localScale", &Transform::localPosition)
               .def_readwrite("parent", &Transform::parent)];
  }
};

#endif

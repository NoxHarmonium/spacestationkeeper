//
//  AxisAlignedBoxBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_AxisAlignedBoxBinders_h
#define SpaceStationKeeper_AxisAlignedBoxBinders_h

#include "ClassBinder.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

template <> struct ClassBinder<AxisAlignedBox3f> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<AxisAlignedBox3f>(name)
                           .def(luabind::constructor<Vec3f, Vec3f>())
                           .def("getCenter", &AxisAlignedBox3f::getCenter)
                           .def("getSize", &AxisAlignedBox3f::getSize)
                           .def("include", &AxisAlignedBox3f::include)
                           .def("getMin", &AxisAlignedBox3f::getMin)
                           .def("getMax", &AxisAlignedBox3f::getMax)
                           .def("getNegative", &AxisAlignedBox3f::getMin)
                           .def("getPositive", &AxisAlignedBox3f::getMax)
                           .def("transformed", &AxisAlignedBox3f::transformed)];
  }
};
}
}
}

#endif

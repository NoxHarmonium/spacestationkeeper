//
//  RenderInfoBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_RenderInfoBinder_h
#define SpaceStationKeeper_RenderInfoBinder_h

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

template <> struct ClassBinder<RenderInfo> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<RenderInfo, RenderInfoRef>(name)
               .def(luabind::constructor<>())
               .def_readwrite("renderEnabled", &RenderInfo::renderEnabled)
               .def_readwrite("transform", &RenderInfo::transform)
               .def_readwrite("mesh", &RenderInfo::mesh)
               .def_readwrite("material", &RenderInfo::material)
               .def("clone", &RenderInfo::clone)
               .def("getBounds", &RenderInfo::getBounds)
               .def("batch", &RenderInfo::batch)
               .def("invalidateBatch", &RenderInfo::invalidateBatch)];
  }
};
}
}
}

#endif

//
//  SteeringTargetBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/07/2014.
//
//

#ifndef SpaceStationKeeper_SteeringTargetBinder_h
#define SpaceStationKeeper_SteeringTargetBinder_h

#include "ClassBinder.h"
#include "SteeringBehaviour.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

using namespace ci::app;
using namespace luabind;
using namespace AI::Steering;

template <> struct ClassBinder<SteeringTarget> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<SteeringTarget, SteeringTargetRef>(name)
               .def(luabind::constructor<Components::RenderableRef>())
               .def("getMaxSpeed", &SteeringTarget::getMaxSpeed)
               .def("setMaxSpeed", &SteeringTarget::setMaxSpeed)
               .def("getSpeed", &SteeringTarget::getSpeed)
               .def("getTransformRef", &SteeringTarget::getTransformRef)
               .def("predictFuturePosition",
                    &SteeringTarget::predictFuturePosition)];
  }
};
}
}
}

#endif

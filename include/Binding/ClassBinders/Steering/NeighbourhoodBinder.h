//
//  NeighbourhoodBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/07/2014.
//
//

#ifndef SpaceStationKeeper_NeighbourhoodBinder_h
#define SpaceStationKeeper_NeighbourhoodBinder_h

#include <memory>
#include "ClassBinder.h"
#include "Neighbourhood.h"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

using namespace ci::app;
using namespace luabind;
using namespace AI::Steering;

/*
 addNeighbour
 removeNeighbour
 getNeighbors void
 getNeighbors vec2 float
 getNeighbors vec2 float float
 addBehaviour
 removeBehaviour



 */

typedef Neighbourhood<SteeringTarget> NeighbourhoodT;
typedef std::shared_ptr<NeighbourhoodT> NeighbourhoodTRef;

template <> struct ClassBinder<NeighbourhoodT> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<NeighbourhoodT, NeighbourhoodTRef>(name)
               .def(luabind::constructor<int>())
               .def("addNeighbour", &NeighbourhoodT::addNeighbour)
               .def("removeNeighbour", &NeighbourhoodT::removeNeighbour)
               .def("getNeighbors",
                    (NeighbourhoodT::TList (NeighbourhoodT::*)()) &
                        NeighbourhoodT::getNeighbors)
               .def("addBehaviour", &NeighbourhoodT::addBehaviour)
               .def("removeBehaviour", &NeighbourhoodT::removeBehaviour)];
  }
};
}
}
}

#endif

//
//  CinderEventBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_CinderEventBinders_h
#define SpaceStationKeeper_CinderEventBinders_h

#include "ClassBinder.h"

using namespace ci::app;

template <> struct ClassBinder<MouseEvent> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<MouseEvent>(name)
                           .def("getX", &MouseEvent::getX)
                           .def("getY", &MouseEvent::getY)
                           .def("getPos", &MouseEvent::getPos)
                           .def("isLeft", &MouseEvent::isLeft)
                           .def("isRight", &MouseEvent::isRight)
                           .def("isMiddle", &MouseEvent::isMiddle)
                           .def("isLeftDown", &MouseEvent::isLeftDown)
                           .def("isRightDown", &MouseEvent::isRightDown)
                           .def("isMiddleDown", &MouseEvent::isMiddleDown)
                           .def("isShiftDown", &MouseEvent::isShiftDown)
                           .def("isAltDown", &MouseEvent::isAltDown)
                           .def("isControlDown", &MouseEvent::isControlDown)
                           .def("isMetaDown", &MouseEvent::isMetaDown)
                           .def("isAccelDown", &MouseEvent::isAccelDown)];
  }
};

#endif

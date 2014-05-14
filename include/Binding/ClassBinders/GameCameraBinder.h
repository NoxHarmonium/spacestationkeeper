//
//  GameCameraBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 9/05/2014.
//
//

#ifndef SpaceStationKeeper_GameCameraBinder_h
#define SpaceStationKeeper_GameCameraBinder_h

#include "ClassBinder.h"
#include "GameCamera.h"

template <> struct ClassBinder<GameCamera> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<GameCamera, GameComponent>(name)
                           .def(luabind::constructor<>())];
  }
};

#endif

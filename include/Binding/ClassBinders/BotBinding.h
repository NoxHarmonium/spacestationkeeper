//
//  BotBinding.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/05/2014.
//
//

#ifndef SpaceStationKeeper_BotBinding_h
#define SpaceStationKeeper_BotBinding_h

#include "ClassBinder.h"
#include "Bot.h"
#include "BotWrapper.h"
#include "BotManager.h"

// Forward Decs
class JobManager;
typedef std::shared_ptr<JobManager> JobManagerRef;

template <> struct ClassBinder<Bot> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Bot, GameComponent, BotWrapper, BotRef>(name)
               .def(luabind::constructor<>())
               .def("getDestination", &Bot::getDestination)
               .def("getSpeed", &Bot::getSpeed)
               .def("willAcceptJob", &Bot::willAcceptJob)
               .def("acceptJob", &Bot::acceptJob)
               .def("update", &Bot::update)];
  }
};

template <> struct ClassBinder<BotManager> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<BotManager, BotManagerRef>(name)
                           .def(luabind::constructor<JobManagerRef>())
                           .def("addCoord", &BotManager::addCoord)
                           .def("removeCoord", &BotManager::removeCoord)
                           .def("addBot", &BotManager::addBot)
                           .def("removeBot", &BotManager::removeBot)];
  }
};

#endif

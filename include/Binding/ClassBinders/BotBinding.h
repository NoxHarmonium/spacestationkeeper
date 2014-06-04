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
#include "BotBehaviourWrapper.h"
#include <iterator_ptr_policy.hpp>

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
               .def("getCoord", &Bot::getCoord)
               .def("getDestination", &Bot::getDestination)
               .def("getSpeed", &Bot::getSpeed)
               .def("willAcceptJob", &Bot::willAcceptJob)
               .def("acceptJob", &Bot::acceptJob)
               .def("getCurrentJob", &Bot::getCurrentJob)
               .def("getState", &Bot::getState)
               .def("setup", &Bot::setup)
               .def("update", &Bot::update)
               .def("addBehaviour", &Bot::addBehaviour)
               .def("removeBehaviour", &Bot::removeBehaviour)
               .def("getBehaviours", &Bot::getBehaviours)
               .enum_("constants")[
                 value("WaitingForJob", 0),
                 value("MovingToJob", 1),
                 value("Working", 2)
               ]];
  }
};

template <> struct ClassBinder<BotManager> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)
        [luabind::class_<BotManager, BotManagerRef>(name)
             .def(luabind::constructor<JobManagerRef>())
             .def("addCoord", &BotManager::addCoord)
             .def("removeCoord", &BotManager::removeCoord)
             .def("addBot", &BotManager::addBot)
             .def("removeBot", &BotManager::removeBot)
             .def("distanceTo", (float (BotManager::*)(Vec2i, Vec2i)) &
                                    BotManager::distanceTo)
             .def("distanceTo", (float (BotManager::*)(Vec2i, Vec2i, int)) &
                                    BotManager::distanceTo)
             .def("getPath", (CoordListRef (BotManager::*)(Vec2i, Vec2i)) &
                                 BotManager::getPath,
                  return_stl_iterator)
             .def("getPath", (CoordListRef (BotManager::*)(Vec2i, Vec2i, int)) &
                                 BotManager::getPath,
                  return_stl_iterator)
             .def("isPassable", &BotManager::isPassable)];
  }
};

template <> struct ClassBinder<BotBehaviour> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<BotBehaviour, BotBehaviourWrapper, BotBehaviourRef>(
               name)
               .def(constructor<>())
               .def("getForce", &BotBehaviour::getForce)];
  }
};

#endif

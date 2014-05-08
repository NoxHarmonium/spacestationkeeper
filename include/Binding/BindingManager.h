//
//  LuaBridge.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 20/04/2014.
//
//

#ifndef __SpaceStationKeeper__LuaBridge__
#define __SpaceStationKeeper__LuaBridge__

#include "LuaBindDeps.h"

extern "C" { int initLuaModules(lua_State *L); }

class BindingManager {
public:
  BindingManager();
  ~BindingManager();

  void initialiseBindings();
  void closeBindings();

private:
  lua_State *L;
  bool _bound = false;
};

#endif /* defined(__SpaceStationKeeper__LuaBridge__) */

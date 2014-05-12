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
#include <string>
#include "GameObject.h"
#include <functional>

extern "C" { int initLuaModules(lua_State *L); }

// Free functions
float app_getDeltaTime();
double app_getElapsedSeconds();
void app_registerGameObject(GameObject *gameObject);
void app_destroyGameObject(GameObject *gameObject);
AssetLoaderBase *app_getAssetLoader();

class BindingManager {
public:
  BindingManager();
  ~BindingManager();

  void initialiseBindings();
  void executeString(std::string program);
  void closeBindings();

  bool catchLuaExceptions(std::function<void()> fn);

  static BindingManager *Instance();

private:
  static BindingManager *_instance;

  lua_State *L;
  bool _bound = false;
};

#endif /* defined(__SpaceStationKeeper__LuaBridge__) */

//
//  LuaBridge.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 20/04/2014.
//
//

#ifndef __SpaceStationKeeper__LuaBridge__
#define __SpaceStationKeeper__LuaBridge__

#include "pch.h"
#include "LuaBindDeps.h"
#include <string>
#include "GameObject.h"
#include <functional>
#include "Job.h"

extern "C" { int initLuaModules(lua_State *L); }

// Free functions
float app_getDeltaTime();
double app_getElapsedSeconds();
void app_registerGameObject(GameObjectRef gameObject);
void app_destroyGameObject(GameObjectRef gameObject);
void app_registerJob(JobRef job);
void app_cancelJob(JobRef job);
AssetLoaderBase *app_getAssetLoader();
int setLuaPath(lua_State *L, const std::string path);

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

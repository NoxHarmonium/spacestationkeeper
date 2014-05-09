//
//  LuaBridge.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 20/04/2014.
//
//

#include "BindingManager.h"
#include "Utils.h"
#include "LuaExecutionException.h"

#include "CinderEventBinders.h"
#include "GameObjectBinder.h"
#include "TransformBinder.h"
#include "BaseMeshBinder.h"
#include "MaterialBinder.h"
#include "RenderInfoBinder.h"
#include "CinderColorBinders.h"
#include "AssetDefBinders.h"
#include "AssetLoadersBinders.h"
#include "AxisAlignedBoxBinders.h"
#include "CinderVecBinders.h"
#include "CinderMatrixBinders.h"

BindingManager::BindingManager() {}

BindingManager::~BindingManager() {
  if (_bound) {
    closeBindings();
  }
}

extern "C" int initLuaModules(lua_State *L) {
  using namespace luabind;
  luabind::open(L);

  // Classes that can be inherited by LUA
  ClassBinder<GameComponent>::Bind("GameComponent", L);

  // Classes directly binded to LUA
  ClassBinder<MouseEvent>::Bind("MouseEvent", L);
  ClassBinder<GameObject>::Bind("GameObject", L);
  ClassBinder<Transform>::Bind("Transform", L);
  ClassBinder<BaseMesh>::Bind("BaseMesh", L);
  ClassBinder<Material>::Bind("Material", L);
  ClassBinder<RenderInfo>::Bind("RenderInfo", L);
  ClassBinder<AssetDefBase>::Bind("AssetDefBase", L);
  ClassBinder<AssetLoaderBase>::Bind("AssetLoaderBase", L);
  ClassBinder<AxisAlignedBox3f>::Bind("AxisAlignedBox3f", L);

  ClassBinder<Color>::Bind("Color", L);
  ClassBinder<Colorf>::Bind("Colorf", L);
  ClassBinder<Color8u>::Bind("Color8u", L);
  ClassBinder<ColorA>::Bind("Color", L);
  ClassBinder<ColorAf>::Bind("Colorf", L);
  ClassBinder<ColorA8u>::Bind("Color8u", L);

  ClassBinder<Vec2i>::Bind("Vec2i", L);
  ClassBinder<Vec2f>::Bind("Vec2f", L);
  ClassBinder<Vec2d>::Bind("Vec2d", L);
  ClassBinder<Vec3i>::Bind("Vec3i", L);
  ClassBinder<Vec3f>::Bind("Vec3f", L);
  ClassBinder<Vec3d>::Bind("Vec3d", L);
  ClassBinder<Vec4i>::Bind("Vec4i", L);
  ClassBinder<Vec4f>::Bind("Vec4f", L);
  ClassBinder<Vec4d>::Bind("Vec4d", L);

  ClassBinder<Matrix44f>::Bind("Matrix44f", L);
  ClassBinder<Matrix44d>::Bind("Matrix44d", L);
  ClassBinder<Matrix33f>::Bind("Matrix33f", L);
  ClassBinder<Matrix33d>::Bind("Matrix33d", L);
  ClassBinder<Matrix22f>::Bind("Matrix22f", L);
  ClassBinder<Matrix22d>::Bind("Matrix22d", L);

  // TODO: Deps
  // Vec3f Matrix44f
  return 0;
}

void BindingManager::initialiseBindings() {
  L = lua_open();

  luaL_openlibs(L);
  luabind::open(L);
  initLuaModules(L);

  _bound = true;
  // luaL_dofile(L, Utils::getResourcesPath() / "init.lua");
}

void BindingManager::executeString(string program) {
  int errorNo = luaL_dostring(L, program.c_str());
  if (errorNo == 1) {
    string errorMessage = lua_tostring(L, -1);
    lua_pop(L, 1); // remove error message
    throw LuaExecutionException(errorMessage);
  }
}

void BindingManager::closeBindings() {
  lua_close(L);
  _bound = false;
}
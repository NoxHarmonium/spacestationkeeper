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
#include "luabind/class_info.hpp"
#include "ComponentDrivenApp.h"

#include <luabind/adopt_policy.hpp>
#include <luabind/shared_ptr_converter.hpp>
#include <luabind/std_shared_ptr_converter.hpp>

#include "GameComponentBinder.h"
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
#include "LuaDebugBinder.h"
#include "CinderQuatBinders.h"
#include "AssetDefBinders.h"
#include "GameCameraBinder.h"
#include "SimpleMeshBinder.h"
#include "CinderRectBinders.h"
#include "BatchedMeshBinder.h"
#include "EnumHelperBinder.h"
#include "JobBinder.h"
#include "UtilsBinder.h"

using adopt2 = luabind::detail::policy_cons<luabind::detail::adopt_policy<2>,
                                            luabind::detail::null_type>;

BindingManager::BindingManager() {}

BindingManager::~BindingManager() {
  if (_bound) {
    closeBindings();
  }
}

float app_getDeltaTime() {
  return ComponentDrivenApp::Instance()->getDeltaTime();
}

double app_getElapsedSeconds() { return ci::app::getElapsedSeconds(); }

void app_registerGameObject(GameObjectRef gameObject) {
  ComponentDrivenApp::Instance()->registerGameObject(gameObject);
}

void app_destroyGameObject(GameObjectRef gameObject) {
  ComponentDrivenApp::Instance()->destroyGameObject(gameObject);
}

void app_registerJob(JobRef job) {
  ComponentDrivenApp::Instance()->getJobManager()->registerJob(job);
}

void app_cancelJob(JobRef job) {
  ComponentDrivenApp::Instance()->getJobManager()->cancelJob(job);
}

int setLuaPath(lua_State *L, const std::string path) {
  lua_getglobal(L, "package");
  lua_getfield(L, -1,
               "path"); // get field "path" from table at top of stack (-1)
  std::string cur_path =
      lua_tostring(L, -1); // grab path string from top of stack
  cur_path += ';';         // do your path magic here
  cur_path += path;
  lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
  lua_pushstring(L, cur_path.c_str()); // push the new one
  lua_setfield(
      L, -2,
      "path"); // set the field "path" in table at -2 with value at top of stack
  lua_pop(L, 1); // get rid of package table from top of stack
  return 0;      // all done!
}

AssetLoaderBase *app_getAssetLoader() {
  return ComponentDrivenApp::Instance()->getAssetLoader();
}

extern "C" int initLuaModules(lua_State *L) {
  using namespace luabind;
  luabind::open(L);

  // Static Utilities
  ClassBinder<LuaDebug>::Bind("LuaDebug", L);

  // Classes that can be inherited by LUA
  ClassBinder<GameComponent>::Bind("GameComponent", L);
  ClassBinder<Job>::Bind("Job", L);

  // Rendering Classes
  ClassBinder<GameCamera>::Bind("GameCamera", L);
  ClassBinder<GameObject>::Bind("GameObject", L);
  ClassBinder<Transform>::Bind("Transform", L);
  ClassBinder<BaseMesh>::Bind("BaseMesh", L);
  ClassBinder<SimpleMesh>::Bind("SimpleMesh", L);
  ClassBinder<Material>::Bind("Material", L);
  ClassBinder<RenderInfo>::Bind("RenderInfo", L);
  ClassBinder<AxisAlignedBox3f>::Bind("AxisAlignedBox3f", L);
  ClassBinder<BatchedMesh>::Bind("BatchedMesh", L);

  // Misc
  ClassBinder<EnumHelper>::Bind("EnumHelper", L);
  ClassBinder<Passibility>::Bind("Passibility", L);
  ClassBinder<Utils>::Bind("Utils", L);

  // Asset Management
  ClassBinder<AssetLoaderBase>::Bind("AssetLoaderBase", L);
  ClassBinder<AssetDefBase>::Bind("AssetDefBase", L);
  ClassBinder<TextureDef>::Bind("TextureDef", L);
  ClassBinder<TileDef>::Bind("TileDef", L);
  ClassBinder<AnimationDef>::Bind("AnimationDef", L);
  ClassBinder<AnimationSetDef>::Bind("AnimationSetDef", L);
  ClassBinder<ShaderDef>::Bind("ShaderDef", L);

  // Cinder event classes
  ClassBinder<MouseEvent>::Bind("MouseEvent", L);
  ClassBinder<KeyEvent>::Bind("KeyEvent", L);

  ClassBinder<Color>::Bind("Color", L);
  ClassBinder<Colorf>::Bind("Colorf", L);
  ClassBinder<Color8u>::Bind("Color8u", L);
  ClassBinder<ColorA>::Bind("ColorA", L);
  ClassBinder<ColorAf>::Bind("ColorAf", L);
  ClassBinder<ColorA8u>::Bind("ColorA8u", L);

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

  ClassBinder<Quatf>::Bind("Quatf", L);
  ClassBinder<Quatd>::Bind("Quatd", L);

  ClassBinder<Rectf>::Bind("Rectf", L);
  ClassBinder<Rectd>::Bind("Rectd", L);

  // App static functions
  module(L)[def("app_getWindowWidth", &ci::app::getWindowWidth)];
  module(L)[def("app_getWindowHeight", &ci::app::getWindowHeight)];
  module(L)[def("app_getDeltaTime", &app_getDeltaTime)];
  module(L)[def("app_registerGameObject", &app_registerGameObject)];
  module(L)[def("app_destroyGameObject", &app_destroyGameObject)];
  module(L)[def("app_getAssetLoader", &app_getAssetLoader)];
  module(L)[def("app_getElapsedSeconds", &app_getElapsedSeconds)];
  module(L)[def("app_registerJob", &app_registerJob)];
  module(L)[def("app_cancelJob", &app_cancelJob)];

  luabind::bind_class_info(L);

  // Make sure require path includes are right
  lua_pushstring(L, "package");
  lua_gettable(L, LUA_GLOBALSINDEX);
  lua_pushstring(L, "cpath");
  lua_pushstring(L, (Utils::getResourcesPath().string() + "/?.so").c_str());
  lua_settable(L, -3);

  // Set path for 'require' lua files
  setLuaPath(L, Utils::getResourcesPath().string() + "/lua/?.lua");

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

bool BindingManager::catchLuaExceptions(std::function<void()> fn) {
  try {
    fn();
  }
  catch (const luabind::error e) {
    cout << "[ERROR] Lua error in GameComponent script: " << lua_tostring(L, -1)
         << endl;
    return true;
  }
  return false;
}

BindingManager *BindingManager::Instance() {
  if (_instance == nullptr) {
    _instance = new BindingManager();
  }
  return _instance;
}

BindingManager *BindingManager::_instance = nullptr;
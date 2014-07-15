//
//  AssetDefBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_AssetDefBinders_h
#define SpaceStationKeeper_AssetDefBinders_h

#include "ClassBinder.h"
#include "AssetDefBase.h"
#include "FixStdSharedPtrBind.h"
#include "TileDef.h"
#include "AnimationDef.h"
#include "AnimationSetDef.h"
#include "luabind/operator.hpp"

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

template <> struct ClassBinder<AssetDefBase> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<AssetDefBase, AssetDefBaseRef>(name)
                           .def("getAssetRef", &AssetDefBase::getAssetRef)
                           .def("setAssetRef", &AssetDefBase::setAssetRef)
                           .def("getId", &AssetDefBase::getId)
                           //.def("getPath", &AssetDefBase::getPath) boost?
                           //.def("setPath", &AssetDefBase::setPath) boost?
                           .def("getAsset", &AssetDefBase::getAsset)
                           .def("assetLoaded", &AssetDefBase::assetLoaded)
                           .def("getAssetType", &AssetDefBase::getAssetType)
                           .def("loadAsset", &AssetDefBase::loadAsset)
                           .def("unloadAsset", &AssetDefBase::unloadAsset)];
  }
};

// TODO: Maybe find a way to use the base class in lua and cast it up when
// you need to assign it to a field but there probably isn't a better way than
// manually defining all these

template <> struct ClassBinder<TextureDef> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<TextureDef, AssetDefBaseT<TextureDef>,
                           TextureDefRef>(name)
               .def("getAssetRef", &TextureDef::getAssetRef)
               .def("setAssetRef", &TextureDef::setAssetRef)
               .def("getId", &TextureDef::getId)
               //.def("getPath", &AssetDefBase::getPath) boost?
               //.def("setPath", &AssetDefBase::setPath) boost?
               .def("getAsset", &AssetDefBaseT<TextureDef>::getAsset)
               .def("assetLoaded", &TextureDef::assetLoaded)
               .def("getAssetType", &TextureDef::getAssetType)
               .def("loadAsset", &TextureDef::loadAsset)
               .def("unloadAsset", &TextureDef::unloadAsset)
               .def("getBorder", &TextureDef::getBorder)
               //.def("getCanWalk", &TextureDef::getCanWalk)
               .def("getFrameCount", &TextureDef::getFrameCount)
               //.def("getFrameFromPassibility",
               //     &TextureDef::getFrameFromPassibility)
               .def("getFrameHeight", &TextureDef::getFrameHeight)
               .def("getFrameSize", &TextureDef::getFrameSize)
               .def("getFrameWidth", &TextureDef::getFrameWidth)
               .def("getWidth", &TextureDef::getWidth)
               .def("getHeight", &TextureDef::getHeight)
               //.def("getPassiblity", &TextureDef::getPassiblity)
               .def("getHeight", &TextureDef::getHeight)
               .def("getFrameUvCoords", &TextureDef::getFrameUvCoords)
               .def(self == self)
               .def(tostring(self))];
  }
};

template <> struct ClassBinder<TileDef> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)
        [luabind::class_<TileDef, TextureDef, TileDefRef>(name)
             .def("getAssetRef", &TileDef::getAssetRef)
             .def("setAssetRef", &TileDef::setAssetRef)
             .def("getId", &TileDef::getId)
             //.def("getPath", &AssetDefBase::getPath) boost?
             //.def("setPath", &AssetDefBase::setPath) boost?
             .def("getAsset", &TextureDef::getAsset)
             .def("assetLoaded", &TileDef::assetLoaded)
             .def("getAssetType", &TileDef::getAssetType)
             .def("loadAsset", &TileDef::loadAsset)
             .def("unloadAsset", &TileDef::unloadAsset)
             .def("getBorder", &TileDef::getBorder)
             .def("getCanWalk", &TileDef::getCanWalk)
             .def("getFrameCount", &TileDef::getFrameCount)
             .def("getFrameFromPassibility", &TileDef::getFrameFromPassibility)
             .def("getFrameHeight", &TileDef::getFrameHeight)
             .def("getFrameSize", &TileDef::getFrameSize)
             .def("getFrameWidth", &TileDef::getFrameWidth)
             .def("getWidth", &TileDef::getWidth)
             .def("getHeight", &TileDef::getHeight)
             .def("getPassiblity", &TileDef::getPassiblity)
             .def("getHeight", &TileDef::getHeight)
             .def("getFrameUvCoords", &TileDef::getFrameUvCoords)];
  }
};

template <> struct ClassBinder<AnimationDef> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<AnimationDef, TextureDef, AnimationDefRef>(name)
               .def("getAssetRef", &TextureDef::getAssetRef)
               .def("setAssetRef", &TextureDef::setAssetRef)
               .def("getId", &TextureDef::getId)
               //.def("getPath", &AssetDefBase::getPath) boost?
               //.def("setPath", &AssetDefBase::setPath) boost?
               .def("getAsset", &AssetDefBaseT<TextureDef>::getAsset)
               .def("assetLoaded", &TextureDef::assetLoaded)
               .def("getAssetType", &TextureDef::getAssetType)
               .def("loadAsset", &TextureDef::loadAsset)
               .def("unloadAsset", &TextureDef::unloadAsset)
               .def("getBorder", &TextureDef::getBorder)
               .def("getFrameCount", &TextureDef::getFrameCount)
               .def("getFrameHeight", &TextureDef::getFrameHeight)
               .def("getFrameSize", &TextureDef::getFrameSize)
               .def("getFrameWidth", &TextureDef::getFrameWidth)
               .def("getWidth", &TextureDef::getWidth)
               .def("getHeight", &TextureDef::getHeight)
               .def("getHeight", &TextureDef::getHeight)
               .def("getFrameUvCoords", &TextureDef::getFrameUvCoords)
               .def("getName", &AnimationDef::getName)
               .def("getFrameStart", &AnimationDef::getFrameStart)
               .def("getFrameEnd", &AnimationDef::getFrameEnd)
               .def("getRate", &AnimationDef::getFrameUvCoords)
               .def("getLoop", &AnimationDef::getFrameUvCoords)];
  }
};

// TODO: These bindings are incorrect. They specify inheritance from
// AssetDefBaseT<ChildClass> where it should be AssetDefBaseT<AssetType> where
// asset type is the type that is returned by get asset (e.g. glslprog or
// texture) If it is specified correctly there is an access violation for some
// reason that needs to be determined. getAsset() will probably crash if called.
template <> struct ClassBinder<AnimationSetDef> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<AnimationSetDef, AssetDefBaseT<AnimationSetDef>,
                           AnimationSetDefRef>(name)
               .def("getAssetRef", &AssetDefBase::getAssetRef)
               .def("setAssetRef", &AssetDefBase::setAssetRef)
               .def("getId", &AssetDefBase::getId)
               //.def("getPath", &AssetDefBase::getPath) boost?
               //.def("setPath", &AssetDefBase::setPath) boost?
               .def("getAsset", &AssetDefBaseT<AnimationSetDef>::getAsset)
               .def("assetLoaded", &AssetDefBase::assetLoaded)
               .def("getAssetType", &AssetDefBase::getAssetType)
               .def("loadAsset", &AssetDefBase::loadAsset)
               .def("unloadAsset", &AssetDefBase::unloadAsset)
               .def("getDefaultAnimation",
                    &AnimationSetDef::getDefaultAnimation)];
  }
};

template <> struct ClassBinder<ShaderDef> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<ShaderDef, AssetDefBaseT<ShaderDef>, ShaderDefRef>(
               name)
               .def("getAssetRef", &AssetDefBase::getAssetRef)
               .def("setAssetRef", &AssetDefBase::setAssetRef)
               .def("getId", &AssetDefBase::getId)
               //.def("getPath", &AssetDefBase::getPath) boost?
               //.def("setPath", &AssetDefBase::setPath) boost?
               .def("getAsset", &AssetDefBaseT<ShaderDef>::getAsset)
               .def("assetLoaded", &AssetDefBase::assetLoaded)
               .def("getAssetType", &AssetDefBase::getAssetType)
               .def("loadAsset", &AssetDefBase::loadAsset)
               .def("unloadAsset", &AssetDefBase::unloadAsset)];
  }
};
}
}
}
#endif

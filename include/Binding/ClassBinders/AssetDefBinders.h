//
//  AssetDefBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_AssetDefBase_h
#define SpaceStationKeeper_AssetDefBase_h

#include "ClassBinder.h"
#include "AssetDefBase.h"

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

#endif

//
//  AssetLoadersBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_AssetLoadersBinders_h
#define SpaceStationKeeper_AssetLoadersBinders_h

#include "ClassBinder.h"
#include "AssetLoaderBase.h"

template <> struct ClassBinder<AssetLoaderBase> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<AssetLoaderBase>(name)
                           .def("loadAsset",
                                (AssetDefBaseRef (AssetLoaderBase::*)(string)) &
                                    AssetLoaderBase::loadAsset)
                           .def("unloadAsset", &AssetLoaderBase::unloadAsset)];
  }
};

#endif

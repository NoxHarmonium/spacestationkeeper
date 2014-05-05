//
//  AssetLoaderBase.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 11/04/2014.
//
//

#include "AssetLoaderBase.h"

// Methods

AssetDefBaseRef AssetLoaderBase::getLoadedAsset(AssetType assetType,
                                                string assetRef) {
  if (_assetMap.count(assetType)) {
    map<string, AssetDefBaseRef> idMap = _assetMap[assetType];
    if (idMap.count(assetRef)) {
      return idMap[assetRef];
    }
  }
  return nullptr;
}

void AssetLoaderBase::saveLoadedAsset(AssetType assetType, string assetRef,
                                      AssetDefBaseRef assetDef) {
  _assetMap[assetType][assetRef] = assetDef;
}

void AssetLoaderBase::clearLoadedAsset(AssetType assetType, string assetRef) {

  if (_assetMap.count(assetType)) {
    _assetMap[assetType].erase(assetRef);
  }
}
//
//  AssetLoaderBase.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 11/04/2014.
//
//

#include "AssetLoaderBase.h"

AssetDefBaseRef AssetLoaderBase::getLoadedAsset(AssetType assetType,
                                                int assetId) {
  if (_assetMap.count(assetType)) {
    map<int, AssetDefBaseRef> idMap = _assetMap[assetType];
    if (idMap.count(assetId)) {
      return idMap[assetId];
    }
  }
  return nullptr;
}

void AssetLoaderBase::saveLoadedAsset(AssetType assetType, int assetId,
                                      AssetDefBaseRef assetDef) {
  if (!_assetMap.count(assetType)) {
    _assetMap[assetType] = map<int, AssetDefBaseRef>();
  }
  _assetMap[assetType][assetId] = assetDef;
}

void AssetLoaderBase::clearLoadedAsset(AssetType assetType, int assetId) {

  if (_assetMap.count(assetType)) {
    _assetMap[assetType].erase(assetId);
  }
}
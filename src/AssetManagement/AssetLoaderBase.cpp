//
//  AssetLoaderBase.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 11/04/2014.
//
//

#include "AssetLoaderBase.h"

AssetDefBase *AssetLoaderBase::GetLoadedAsset(AssetType assetType,
                                              int assetId) {
  if (_assetMap.count(assetType)) {
    map<int, AssetDefBase *> idMap = _assetMap[assetType];
    if (idMap.count(assetId)) {
      return idMap[assetId];
    }
  }
  return nullptr;
}

void AssetLoaderBase::SaveLoadedAsset(AssetType assetType, int assetId,
                                      AssetDefBase *assetDef) {
  if (!_assetMap.count(assetType)) {
    _assetMap[assetType] = map<int, AssetDefBase *>();
  }
  _assetMap[assetType][assetId] = assetDef;
}

void AssetLoaderBase::ClearLoadedAsset(AssetType assetType, int assetId) {

  if (_assetMap.count(assetType)) {
    _assetMap[assetType].erase(assetId);
  }
}
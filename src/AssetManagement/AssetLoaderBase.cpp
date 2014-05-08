//
//  AssetLoaderBase.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 11/04/2014.
//
//

#include "AssetLoaderBase.h"

// Methods

AssetDefBaseRef AssetLoaderBase::loadAsset(string assetRef) {
  AssetDefBaseRef storedAsset = getLoadedAsset(assetRef);
  if (storedAsset) {
    cout << "Cache hit on: \"" << assetRef << "\". Not loading again." << endl;
    return storedAsset;
  }
  return nullptr;
}

AssetDefBaseRef AssetLoaderBase::getLoadedAsset(string assetRef) {

  if (_assetMap.count(assetRef)) {
    return _assetMap[assetRef];
  }

  return nullptr;
}

void AssetLoaderBase::saveLoadedAsset(string assetRef,
                                      AssetDefBaseRef assetDef) {
  _assetMap[assetRef] = assetDef;
}

void AssetLoaderBase::clearLoadedAsset(string assetRef) {

  _assetMap.erase(assetRef);
}
//
//  AssetLoaderBase.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#ifndef __SpaceStationKeeper__AssetLoaderBase__
#define __SpaceStationKeeper__AssetLoaderBase__

#include <stdlib.h>
#include "AssetDefBase.h"
#include "AssetType.h"
#include "filesystem.hpp"

using namespace std;
using namespace boost;

class AssetDefBase; // Required def cyclic dependency
typedef std::shared_ptr<AssetDefBase> AssetDefBaseRef;

class AssetLoaderBase {
public:
  // template <typename T>
  // std::shared_ptr<T>
  // LoadAsset(string assetRef) {}; // Can a template be virtual? How specify
  // interface?
  virtual void UnloadAsset(AssetDefBaseRef asset) = 0;
  AssetDefBaseRef GetLoadedAsset(AssetType assetType, int assetId);

protected:
  void SaveLoadedAsset(AssetType assetType, int assetId,
                       AssetDefBaseRef assetDef);

  void ClearLoadedAsset(AssetType assetType, int assetId);

private:
  map<AssetType, map<int, AssetDefBaseRef>> _assetMap;
  // const path _assetDefFileName = path("assetdef.yaml";
};

#endif /* defined(__SpaceStationKeeper__AssetLoaderBase__) */

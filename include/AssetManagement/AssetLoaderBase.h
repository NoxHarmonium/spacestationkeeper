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
  virtual AssetDefBaseRef LoadAsset(string assetRef) = 0;
  template <typename T> std::shared_ptr<T> loadAsset(string assetRef) {
    return std::dynamic_pointer_cast<T>(LoadAsset(assetRef));
  }

  virtual void unloadAsset(AssetDefBaseRef asset) = 0;
  AssetDefBaseRef getLoadedAsset(AssetType assetType, int assetId);

protected:
  void saveLoadedAsset(AssetType assetType, int assetId,
                       AssetDefBaseRef assetDef);

  void clearLoadedAsset(AssetType assetType, int assetId);

private:
  map<AssetType, map<int, AssetDefBaseRef>> _assetMap;
  // const path _assetDefFileName = path("assetdef.yaml";
};

#endif /* defined(__SpaceStationKeeper__AssetLoaderBase__) */

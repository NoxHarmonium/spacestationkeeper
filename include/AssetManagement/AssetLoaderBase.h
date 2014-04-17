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

class AssetLoaderBase {
public:
  virtual AssetDefBase *LoadAsset(string assetRef) = 0;
  virtual void UnloadAsset(AssetDefBase *asset) = 0;
  AssetDefBase *GetLoadedAsset(AssetType assetType, int assetId);

protected:
  void SaveLoadedAsset(AssetType assetType, int assetId,
                       AssetDefBase *assetDef);

  void ClearLoadedAsset(AssetType assetType, int assetId);

private:
  map<AssetType, map<int, AssetDefBase *>> _assetMap;
  // const path _assetDefFileName = path("assetdef.yaml";
};

#endif /* defined(__SpaceStationKeeper__AssetLoaderBase__) */
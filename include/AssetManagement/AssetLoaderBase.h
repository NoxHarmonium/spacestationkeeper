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

// Required defs for cyclic dependency
class AssetDefBase;
template <typename T> struct GetAssetType;
typedef std::shared_ptr<AssetDefBase> AssetDefBaseRef;

class AssetLoaderBase {
public:
  virtual AssetDefBaseRef LoadAsset(string assetRef) = 0;
  template <typename T> std::shared_ptr<T> loadAsset(string assetRef) {
    AssetDefBaseRef storedAsset =
        getLoadedAsset(GetAssetType<T>::value, assetRef);
    if (storedAsset) {
      cout << "Cache hit on: \"" << assetRef << "\". Not loading again."
           << endl;
      return std::dynamic_pointer_cast<T>(storedAsset);
    }

    return std::dynamic_pointer_cast<T>(LoadAsset(assetRef));
  }

  virtual void unloadAsset(AssetDefBaseRef asset) = 0;

  AssetDefBaseRef getLoadedAsset(AssetType assetType, string assetRef);

protected:
  void saveLoadedAsset(AssetType assetType, string assetRef,
                       AssetDefBaseRef assetDef);

  void clearLoadedAsset(AssetType assetType, string assetRef);

private:
  map<AssetType, map<string, AssetDefBaseRef>> _assetMap;
  // const path _assetDefFileName = path("assetdef.yaml";
};

#endif /* defined(__SpaceStationKeeper__AssetLoaderBase__) */

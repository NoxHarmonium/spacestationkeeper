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

namespace BlazeEngine {
namespace AssetManagement {

using namespace std;
using namespace boost;

// Required defs for cyclic dependency
class AssetDefBase;
template <typename T> class AssetDefBaseT;
template <typename T> struct GetAssetType;
typedef std::shared_ptr<AssetDefBase> AssetDefBaseRef;

class AssetLoaderBase {
public:
  // Methods
  /*! Loads an asset reference from an AssetRef string (relative path from the
   * assetn directory) and stores it in memory. */
  virtual AssetDefBaseRef loadAsset(string assetRef);
  /*! Unloads an AssetRef file from memory. */
  virtual void unloadAsset(AssetDefBaseRef asset) = 0;

  AssetDefBaseRef getLoadedAsset(string assetRef);

  // Template Methods
  /*! Type specific asset load method. */
  // TODO: Implement caching in generic loadAsset() method?
  template <typename T> std::shared_ptr<T> loadAsset(string assetRef) {
    return std::dynamic_pointer_cast<T>(loadAsset(assetRef));
  }

protected:
  // Methods
  /*! Stores an assetRef in the cache referenced by type and assetRef string. */
  void saveLoadedAsset(string assetRef, AssetDefBaseRef assetDef);
  /*! Removes an asserRef from the cache referenced by type and assetRef string.
   */
  void clearLoadedAsset(string assetRef);

private:
  // Fields
  /*! Maps asset types and assetRef strings to assetRefs. */
  map<string, AssetDefBaseRef> _assetMap;
};
}
}

#endif /* defined(__SpaceStationKeeper__AssetLoaderBase__) */

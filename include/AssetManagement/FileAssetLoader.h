//
//  FileAssetLoader.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#ifndef __SpaceStationKeeper__FileAssetLoader__
#define __SpaceStationKeeper__FileAssetLoader__

#include "AssetLoaderBase.h"

namespace BlazeEngine {
namespace AssetManagement {

using namespace boost;

class FileAssetLoader : public AssetLoaderBase {

public:
  // Constuctors/Destructors
  FileAssetLoader(filesystem::path assetRoot);
  ~FileAssetLoader();

  // Methods
  /*! Loads an asset reference from an AssetRef string (relative path from the
   * assets directory) and stores it in memory. */
  AssetDefBaseRef loadAsset(string assetRef);
  /*! Unloads an AssetRef file from memory. */
  void unloadAsset(AssetDefBaseRef asset);
  /*! Gets the root directory of the assets (i.e. the directory that all assets
   * are references relatively from). */
  filesystem::path getAssetRoot();

private:
  /*! Stores the root directory of the assets (i.e. the directory that all
   * assets
   * are references relatively from). */
  filesystem::path _assetRoot;
};
}
}

#endif /* defined(__SpaceStationKeeper__FileAssetLoader__) */

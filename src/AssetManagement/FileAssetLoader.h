//
//  FileAssetLoader.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#ifndef __SpaceStationKeeper__FileAssetLoader__
#define __SpaceStationKeeper__FileAssetLoader__

#define TEXTUREDEF_TYPE "TextureDef"

#include <stdlib.h>
#include <iostream>
#include "AssetLoaderBase.h"
#include "boost/filesystem/fstream.hpp"
#include "yaml.h"
#include "TextureDef.h"
#include "AssetDefConverters.h"

using namespace boost;

class FileAssetLoader : public AssetLoaderBase {

public:
  FileAssetLoader(filesystem::path assetRoot);
  AssetDefBase *LoadAsset(string assetRef);
  void UnloadAsset(AssetDefBase *asset);
  filesystem::path getAssetRoot();

private:
  filesystem::path _assetRoot;
};

#endif /* defined(__SpaceStationKeeper__FileAssetLoader__) */

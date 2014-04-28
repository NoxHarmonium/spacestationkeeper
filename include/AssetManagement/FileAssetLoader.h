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
#include "ShaderDef.h"

using namespace boost;

class FileAssetLoader : public AssetLoaderBase {

public:
  FileAssetLoader(filesystem::path assetRoot);

  template <typename T> std::shared_ptr<T> loadAsset(string assetRef) {
    // WHAT THE DAMN HELL?!?! Why does this need to be in the header?
    // When I try to put it in the cpp file it doesn't seem to compile.

    cout << "FileAssetLoader::loadAsset()" << endl;

    filesystem::ifstream ifs;
    filesystem::path path = getAssetRoot() / filesystem::path(assetRef) /
                            filesystem::path(ASSETDEF_FILE);

    cout << "Loading path: " << path << endl;

    ifs.open(path);
    if (ifs.is_open()) {

      YAML::Node node = YAML::Load(ifs);
      ifs.close();

      // cout << "Yaml dump: " << YAML::Dump(node) << endl;

      AssetType assetType = node["type"].as<AssetType>();

      // TODO: Verify that AssetType matches the template type

      static T assetDef = node.as<T>();
      assetDef.setPath(path.parent_path()); // Get directory of asset
      std::shared_ptr<T> assetDefRef = std::shared_ptr<T>(&assetDef);
      saveLoadedAsset(assetType, assetDef.getId(), assetDefRef);
      return assetDefRef;
    }

    // Load error
    throw new std::exception();
  }
  void unloadAsset(AssetDefBaseRef asset);
  filesystem::path getAssetRoot();

private:
  filesystem::path _assetRoot;
};

#endif /* defined(__SpaceStationKeeper__FileAssetLoader__) */

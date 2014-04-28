//
//  FileAssetLoader.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#include "FileAssetLoader.h"

using namespace std;
using namespace boost;

FileAssetLoader::FileAssetLoader(filesystem::path assetRoot) {
  _assetRoot = assetRoot;
}

filesystem::path FileAssetLoader::getAssetRoot() {
  return _assetRoot / filesystem::path("assets");
}
/*
template <typename T>
std::shared_ptr<T> FileAssetLoader::loadAsset(string assetRef) {
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
    saveLoadedAsset(assetType, assetDef, assetDefRef);
    return assetDefRef;
  }

  // Load error
  throw new std::exception();
}*/
void FileAssetLoader::unloadAsset(AssetDefBaseRef asset) {
  clearLoadedAsset(AssetType::Texture, asset->getId());
}
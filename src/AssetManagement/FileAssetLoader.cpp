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

AssetDefBaseRef FileAssetLoader::LoadAsset(string assetRef) {
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

    switch (assetType) {
    case AssetType::Texture: {
      static TextureDef tDef = node.as<TextureDef>();
      tDef.setPath(path.parent_path()); // Get directory of asset
      tDef.setAssetRef(assetRef);
      AssetDefBaseRef tDefRef = AssetDefBaseRef((AssetDefBase *)(&tDef));
      saveLoadedAsset(AssetType::Texture, tDef.getId(), tDefRef);
      return tDefRef;
    }
    case AssetType::Shader: {
      static ShaderDef sDef = node.as<ShaderDef>();
      sDef.setPath(path.parent_path()); // Get directory of asset
      sDef.setAssetRef(assetRef);
      AssetDefBaseRef sDefRef = AssetDefBaseRef((AssetDefBase *)(&sDef));
      saveLoadedAsset(AssetType::Shader, sDef.getId(), sDefRef);
      return sDefRef;
    }
    default: {
      throw new Exception(); // Not implemented
    }
    }
  }

  // Load error
  throw new std::exception();
}

void FileAssetLoader::unloadAsset(AssetDefBaseRef asset) {
  clearLoadedAsset(AssetType::Texture, asset->getId());
}
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

AssetDefBase *FileAssetLoader::LoadAsset(string assetRef) {
  cout << "FileAssetLoader::LoadAsset()" << endl;

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
      SaveLoadedAsset(AssetType::Texture, tDef.getId(), &tDef);
      return (AssetDefBase *)(&tDef);
    }
      case AssetType::Shader: {
        static ShaderDef sDef = node.as<ShaderDef>();
        sDef.setPath(path.parent_path()); // Get directory of asset
        SaveLoadedAsset(AssetType::Shader, sDef.getId(), &sDef);
        return (AssetDefBase *)(&sDef);
      }
    default: {
      throw new Exception(); // Not implemented
    }
    }
  }

  // Load error
  throw new std::exception();
}
void FileAssetLoader::UnloadAsset(AssetDefBase *asset) {
  ClearLoadedAsset(AssetType::Texture, asset->getId());
}
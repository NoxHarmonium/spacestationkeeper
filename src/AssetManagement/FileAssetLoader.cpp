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
      // if (node["id"])

      TextureDefRef tDef = TextureDef::FromYamlNode(node);
      tDef->setPath(path.parent_path()); // Get directory of asset
      tDef->setAssetRef(assetRef);
      AssetDefBaseRef tDefBase = dynamic_pointer_cast<AssetDefBase>(tDef);
      saveLoadedAsset(AssetType::Texture, assetRef, tDefBase);
      return tDefBase;
    }
    case AssetType::Shader: {
      ShaderDefRef sDef = ShaderDef::FromYamlNode(node);
      sDef->setPath(path.parent_path()); // Get directory of asset
      sDef->setAssetRef(assetRef);
      AssetDefBaseRef sDefBase = dynamic_pointer_cast<AssetDefBase>(sDef);
      saveLoadedAsset(AssetType::Shader, assetRef, sDefBase);
      return sDefBase;
    }
    default: {
      throw new std::exception(); // Not implemented
    }
    }
  }

  // Load error
  throw new std::exception();
}

void FileAssetLoader::unloadAsset(AssetDefBaseRef asset) {
  // TODO: Work this out properly
}
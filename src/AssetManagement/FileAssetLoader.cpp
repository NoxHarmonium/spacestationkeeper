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

// Constructors/Destructors

FileAssetLoader::FileAssetLoader(filesystem::path assetRoot) {
  _assetRoot = assetRoot;
}

FileAssetLoader::~FileAssetLoader() {}

// Methods

filesystem::path FileAssetLoader::getAssetRoot() {
  return _assetRoot / filesystem::path("assets");
}

AssetDefBaseRef FileAssetLoader::loadAsset(string assetRef) {
  cout << "FileAssetLoader::loadAsset()" << endl;

  filesystem::ifstream ifs;
  filesystem::path path = getAssetRoot() / filesystem::path(assetRef) /
                          filesystem::path(ASSETDEF_FILE);

  cout << "Loading path: " << path << endl;

  try {
    ifs.open(path);
  }
  catch (const std::exception &e) {
    throw new AssetLoadException(&e);
  }
  if (ifs.is_open()) {
    YAML::Node node;
    try {
      node = YAML::Load(ifs);
      ifs.close();
    }
    catch (const std::exception &e) {
      throw new AssetLoadException(
          AssetLoadException::AssetLoadExceptionReason::YamlParseError,
          e.what());
    }

    AssetType assetType;
    Utils::parseNode(&assetType, node, "type");

    switch (assetType) {
    case AssetType::Texture: {
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
      throw new AssetLoadException(
          AssetLoadException::AssetLoadExceptionReason::UnsupportedAssetType);
    }
    }
  }

  throw new AssetLoadException(
      AssetLoadException::AssetLoadExceptionReason::UnknownError);
}

void FileAssetLoader::unloadAsset(AssetDefBaseRef asset) {
  clearLoadedAsset(asset->getAssetType(), asset->getAssetRef());
}
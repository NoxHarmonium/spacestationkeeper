//
//  FileAssetLoader.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#include "FileAssetLoader.h"
#include "boost/filesystem/fstream.hpp"
#include "yaml-cpp/yaml.h"
#include "AssetDefConverters.h"
#include "TextureDef.h"
#include "TileDef.h"
#include "ShaderDef.h"
#include "ScriptDef.h"

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
  // cout << "FileAssetLoader::loadAsset()" << endl;

  AssetDefBaseRef cachedAsset = AssetLoaderBase::loadAsset(assetRef);
  if (cachedAsset != nullptr) {
    return cachedAsset;
  }

  filesystem::ifstream ifs;
  // Make the ifstream throw exceptions on error
  ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  filesystem::path path = getAssetRoot() / filesystem::path(assetRef) /
                          filesystem::path(ASSETDEF_FILE);

  // cout << "Loading path: " << path << endl;

  if (!filesystem::exists(path) || filesystem::is_directory(path)) {
    throw AssetLoadException(
        AssetLoadException::AssetLoadExceptionReason::InvalidPath);
  }

  try {
    ifs.open(path);
  }
  catch (const std::ifstream::failure &e) {
    throw AssetLoadException(&e);
  }
  if (ifs.is_open()) {
    YAML::Node node;
    try {
      node = YAML::Load(ifs);
      ifs.close();
    }
    catch (const std::exception &e) {
      throw AssetLoadException(
          AssetLoadException::AssetLoadExceptionReason::YamlParseError,
          e.what());
    }

    AssetType assetType;
    Utils::parseNode(&assetType, node, "type");

    switch (assetType) {
    case AssetType::Texture: {
      TextureDef::TextureType subType;
      TextureDefRef tDef;
      Utils::parseNode(&subType, node, "subtype");

      switch (subType) {
      case TextureDef::TextureType::Tile: {
        tDef = dynamic_pointer_cast<TextureDef>(TileDef::FromYamlNode(node));
        break;
      }
      case TextureDef::TextureType::Animation: {
        throw NotImplementedException();
        break;
      }
      default: {
        throw NotImplementedException();
        break;
      }
      }

      tDef->setPath(path.parent_path()); // Get directory of asset
      tDef->setAssetRef(assetRef);
      AssetDefBaseRef tDefBase = dynamic_pointer_cast<AssetDefBase>(tDef);
      saveLoadedAsset(assetRef, tDefBase);
      return tDefBase;
    }
    case AssetType::Shader: {
      ShaderDefRef sDef = ShaderDef::FromYamlNode(node);
      sDef->setPath(path.parent_path()); // Get directory of asset
      sDef->setAssetRef(assetRef);
      AssetDefBaseRef sDefBase = dynamic_pointer_cast<AssetDefBase>(sDef);
      saveLoadedAsset(assetRef, sDefBase);
      return sDefBase;
    }
    case AssetType::Script: {
      ScriptDefRef sDef = ScriptDef::FromYamlNode(node);
      sDef->setPath(path.parent_path()); // Get directory of asset
      sDef->setAssetRef(assetRef);
      AssetDefBaseRef sDefBase = dynamic_pointer_cast<AssetDefBase>(sDef);
      saveLoadedAsset(assetRef, sDefBase);
      return sDefBase;
    }
    default: {
      throw AssetLoadException(
          AssetLoadException::AssetLoadExceptionReason::UnsupportedAssetType);
    }
    }
  }

  throw AssetLoadException(
      AssetLoadException::AssetLoadExceptionReason::UnknownError);
}

void FileAssetLoader::unloadAsset(AssetDefBaseRef asset) {
  clearLoadedAsset(asset->getAssetRef());
}
//
//  AssetDefConverters.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#include "yaml.h"
#include "AssetType.h"
#include "ShaderDef.h"
#include "Passibility.h"
#include "Utils.h"
#include "NotImplementedException.h"

#ifndef __SpaceStationKeeper__AssetDefConverters__
#define __SpaceStationKeeper__AssetDefConverters__

//
// YAML node conversion specializations
// This file contains specializations so that certain types can be
// directly converted from YAML nodes using the YAML::Node.as<T>() method.
//

namespace YAML {
using namespace std;
using namespace ci;

template <> struct convert<AssetType> {

  static Node encode(const AssetType &assetType) {
    // Not required yet
    throw new NotImplementedException();
  }

  static bool decode(const Node &node, AssetType &assetType) {

    string type = node.as<string>();
    if (type.compare(ASSET_TEXTURE) == 0) {
      assetType = AssetType::Texture;
    } else if (type.compare(ASSET_AUDIO) == 0) {
      assetType = AssetType::Audio;
    } else if (type.compare(ASSET_SHADER) == 0) {
      assetType = AssetType::Shader;
    } else {
      assetType = AssetType::Unknown;
    }

    return true;
  }
};

template <> struct convert<ShaderDef::ShaderType> {
  static Node encode(const ShaderDef::ShaderType &shaderType) {
    // Not required yet
    throw new NotImplementedException();
  }

  static bool decode(const Node &node, ShaderDef::ShaderType &shaderType) {

    string type = node.as<string>();
    if (type.compare(SHADER_FRAGMENT) == 0) {
      shaderType = ShaderDef::ShaderType::Fragment;
    } else if (type.compare(SHADER_VERTEX) == 0) {
      shaderType = ShaderDef::ShaderType::Vertex;
    } else if (type.compare(SHADER_GEOMETERY) == 0) {
      shaderType = ShaderDef::ShaderType::Geometry;
    } else {
      shaderType = ShaderDef::ShaderType::Unknown;
    }

    return true;
  }
};
template <> struct convert<Passibility> {
  static Node encode(const AssetType &assetType) {
    // Not required yet
    throw new NotImplementedException();
  }

  static bool decode(const Node &node, Passibility &passibility) {
    string passString = node.as<string>();

    // cout << "passString: " << passString << " ";

    if (Utils::existsIn(passString, "-")) {
      // Tile is unused
      passibility.setFlag(E_Passibility::Unused);
      return true;
    }

    if (passString == "") {
      // No direction is passable
      passibility.setFlag(E_Passibility::None);
      return true;
    }

    if (Utils::existsIn(passString, "n")) {
      passibility.setFlag(E_Passibility::North);
    }
    if (Utils::existsIn(passString, "e")) {
      passibility.setFlag(E_Passibility::East);
    }
    if (Utils::existsIn(passString, "s")) {
      passibility.setFlag(E_Passibility::South);
    }
    if (Utils::existsIn(passString, "w")) {
      passibility.setFlag(E_Passibility::West);
    }

    //    cout << " " << passibility << endl;

    return true;
  }
};
}

#endif
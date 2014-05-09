//
//  AssetDefConverters.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#include "yaml-cpp/yaml.h"
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
    throw NotImplementedException();
  }

  static bool decode(const Node &node, AssetType &assetType) {

    string type = node.as<string>();
    if (type.compare(ASSET_TEXTURE) == 0) {
      assetType = AssetType::Texture;
    } else if (type.compare(ASSET_AUDIO) == 0) {
      assetType = AssetType::Audio;
    } else if (type.compare(ASSET_SHADER) == 0) {
      assetType = AssetType::Shader;
    } else if (type.compare(ASSET_SCRIPT) == 0) {
      assetType = AssetType::Script;
    } else {
      assetType = AssetType::Unknown;
    }

    return true;
  }
};

template <> struct convert<ShaderDef::ShaderType> {
  static Node encode(const ShaderDef::ShaderType &shaderType) {
    // Not required yet
    throw NotImplementedException();
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
    throw NotImplementedException();
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

template <typename T> struct convert<Vec2<T>> {

  static Node encode(const Vec2<T> &v) {
    Node n;
    n[0] = v.x;
    n[1] = v.y;
    return n;
  }

  static bool decode(const Node &node, Vec2<T> &v) {
    v.x = node[0].as<T>();
    v.y = node[1].as<T>();
    return true;
  }
};

template <typename T> struct convert<Vec3<T>> {

  static Node encode(const Vec3<T> &v) {
    Node n;
    n[0] = v.x;
    n[1] = v.y;
    n[2] = v.z;
    return n;
  }

  static bool decode(const Node &node, Vec3<T> &v) {
    v.x = node[0].as<T>();
    v.y = node[1].as<T>();
    v.z = node[2].as<T>();
    return true;
  }
};

template <typename T> struct convert<Quaternion<T>> {

  static Node encode(const Quaternion<T> &q) {
    Node n;
    n[0] = q.w;
    n[1] = q.v;
    return n;
  }

  static bool decode(const Node &node, Quaternion<T> &q) {
    q.w = node[0].as<T>();
    q.v = Vec3<T>(node[1].as<T>(), node[2].as<T>(), node[3].as<T>());
    return true;
  }
};
}

#endif
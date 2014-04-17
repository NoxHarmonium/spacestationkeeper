//
//  AssetDefConverters.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#include "yaml.h"
#include "TextureDef.h"
#include "ShaderDef.h"
#include "AssetType.h"
#include "Passibility.h"
#include "Utils.h"

namespace YAML {
using namespace std;
using namespace ci;

template <> struct convert<TextureDef> {
  static Node encode(const TextureDef &textureDef) {
    throw new std::exception(); // Not implemented
  }

  static bool decode(const Node &node, TextureDef &textureDef) {
    /* Example format
    --- # Texture Def
  width:          256
  height:         256
  frameHeight:    64
  frameWidth:     64
  source:         "tileset_corridor.png" */
    int id = node["id"].as<int>();
    int width = node["width"].as<int>();
    int height = node["height"].as<int>();
    int frameHeight = node["frameHeight"].as<int>();
    int frameWidth = node["frameWidth"].as<int>();
    string source = node["source"].as<string>();
    // gl::Texture texture = loadImage(source);

    cout << "Deserialising TextureDef..." << endl;
    // cout << "width: " << width << endl;
    // cout << "height: " << height << endl;
    // cout << "frameHeight: " << frameHeight << endl;
    // cout << "frameWidth: " << frameWidth << endl;
    // cout << "source: " << source << endl;

    // TODO: Validate and return false if invalid.
    textureDef.setValues(id, width, height, frameHeight, frameWidth, source);

    if (node["passibility"]) {
      // cout << "passibility node detected..." << endl;
      Node pRef = node["passibility"];
      // cout << "pRef: " << pRef << endl;
      // TODO: Code to parse passibility
      for (int i = 0; i < textureDef.getFrameCount(); i++) {
        if (pRef[i]) {
          Passibility p = pRef[i].as<Passibility>();
          textureDef.setPassiblity(i, p);
          // cout << "Passibility: (" << i << "): " << p << endl;
        }
      }
    }

    /*
        textureDef.width = node["width"].as<int>();
        textureDef.height = node["height"].as<int>();
        textureDef.frameHeight = node["frameHeight"].as<int>();
        textureDef.frameWidth = node["frameWidth"].as<int>();
        textureDef.source = node["source"].as<string>();
     */

    return true;
  }
};

template <> struct convert<ShaderDef> {
  static Node encode(const ShaderDef &textureDef) {
    throw new std::exception(); // Not implemented
  }

  static bool decode(const Node &node, ShaderDef &textureDef) {

    cout << "Deserialising ShaderDef... ";

    int id = node["id"].as<int>();

    map<ShaderDef::ShaderType, string> _filenameMap;

    Node components = node["components"];
    if (components["vertex"]) {
      cout << "vertex ";
      string source = components["vertex"]["source"].as<string>();
      _filenameMap[ShaderDef::ShaderType::Vertex] = source;
    }
    if (components["fragment"]) {
      cout << "fragment ";
      string source = components["fragment"]["source"].as<string>();
      _filenameMap[ShaderDef::ShaderType::Fragment] = source;
    }
    if (components["geometry"]) {
      cout << "geometry ";
      string source = components["geometry"]["source"].as<string>();
      _filenameMap[ShaderDef::ShaderType::Geometry] = source;
    }

    cout << endl;

    // TODO: Validate and return false if invalid.
    textureDef.setValues(id, _filenameMap);

    return true;
  }
};

template <> struct convert<AssetType> {
  static Node encode(const AssetType &assetType) {
    throw new std::exception(); // Not implemented
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
    throw new std::exception(); // Not implemented
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
    throw new std::exception(); // Not implemented
  }

  static bool decode(const Node &node, Passibility &passibility) {
    string passString = node.as<string>();

    // cout << "passString: " << passString << " ";

    if (Utils::existsIn(passString, "-")) {
      // Skip
      // cout << "-";
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

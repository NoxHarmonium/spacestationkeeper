//
//  TextureDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 25/03/2014.
//
//

#include "TextureDef.h"
using namespace std;

TextureDef TextureDef::loadFromPath(std::string path) {
  ifstream ifs;
  ifs.open(path);
  if (ifs.is_open()) {
    YAML::Node node = YAML::Load(ifs);
    ifs.close();
    TextureDef td = node.as<TextureDef>();
    return td;
  } else {
    // Load error
    throw new std::exception();
  }
}

namespace YAML {
using namespace std;

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
     source:         "tileset_corridor.png"
     */

    // TODO: Validate and return false if invalid.

    textureDef.width = node["width"].as<int>();
    textureDef.height = node["height"].as<int>();
    textureDef.frameHeight = node["frameHeight"].as<int>();
    textureDef.frameWidth = node["frameWidth"].as<int>();
    textureDef.source = node["source"].as<string>();

    return true;
  }
};
}
//
//  TextureDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 19/03/2014.
//
//

#ifndef SpaceStationKeeper_TextureDef_h
#define SpaceStationKeeper_TextureDef_h

#include "yaml.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include <iostream>
#include <fstream>

class TextureDef {
public:
  int width;
  int height;
  int frameHeight;
  int frameWidth;
  std::string source;

  static TextureDef loadFromPath(std::string path);
};

#endif

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
#include "AssetDefBase.h"
#include <iostream>
#include <fstream>
#include "Passibility.h"

using namespace std;
using namespace ci;

class TextureDef : public AssetDefBase {
public:
  TextureDef();
  TextureDef(int width, int height, int frameHeight, int frameWidth,
             string source);

  void setValues(int width, int height, int frameHeight, int frameWidth,
                 string source);
  int getWidth();
  int getHeight();
  int getFrameHeight();
  int getFrameWidth();
  string getSource();
  gl::Texture useTexture();
  void releaseTexture();
  void setPath(filesystem::path path);
  filesystem::path getPath();
  Passibility getPassiblity(int frameNumber);
  void setPassiblity(int frameNumber, Passibility passability);

  int getFrameCount();

  // conversion from A (constructor):
  TextureDef(const AssetDefBase &x) {}
  // conversion from A (assignment):
  TextureDef &operator=(const AssetDefBase &x) { return *this; }

private:
  int _width;
  int _height;
  int _frameHeight;
  int _frameWidth;
  string _source;
  filesystem::path _path;
  gl::Texture *_texture = nullptr;
  Passibility *_passibilities;
};

#endif

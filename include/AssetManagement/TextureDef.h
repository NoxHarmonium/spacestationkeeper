//
//  TextureDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 19/03/2014.
//
//

#ifndef SpaceStationKeeper_TextureDef_h
#define SpaceStationKeeper_TextureDef_h

#include <stdlib.h>
#include <map>
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
  TextureDef(int id, int width, int height, int frameHeight, int frameWidth,
             string filename, bool canWalk);

  void setValues(int id, int width, int height, int frameHeight, int frameWidth,
                 string filename, bool canWalk);
  int getWidth();
  int getHeight();
  int getFrameHeight();
  int getFrameWidth();
  bool getCanWalk();
  Rectf getFrameSize();
  string getFilename();
  gl::TextureRef useTexture();
  void releaseTexture();
  void setPath(filesystem::path path);
  filesystem::path getPath();
  Passibility getPassiblity(int frameNumber);
  void setPassiblity(int frameNumber, Passibility passability);
  int getFrameFromPassibility(Passibility passability);
  int getFrameCount();

  static std::shared_ptr<TextureDef> FromYamlNode(YAML::Node node);

private:
  int _width;
  int _height;
  int _frameHeight;
  int _frameWidth;
  bool _canWalk;
  string _filename;
  filesystem::path _path;
  gl::TextureRef _texture = nullptr;
  Passibility *_passibilities;
  map<int, int> _passabilityMap;
};

typedef std::shared_ptr<TextureDef> TextureDefRef;

template <> struct GetAssetType<TextureDef> {
  static const AssetType value = AssetType::Texture;
};

#endif

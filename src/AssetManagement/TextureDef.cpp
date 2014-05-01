//
//  TextureDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 25/03/2014.
//
//

#include "TextureDef.h"
#include "AssetDefConverters.h"

using namespace std;
using namespace YAML;

TextureDef::TextureDef() {};
TextureDef::TextureDef(int id, int width, int height, int frameHeight,
                       int frameWidth, string filename) {
  setValues(id, width, height, frameHeight, frameWidth, filename);
}
void TextureDef::setValues(int id, int width, int height, int frameHeight,
                           int frameWidth, string filename) {
  _id = id;
  _width = width;
  _height = height;
  _frameHeight = frameHeight;
  _frameWidth = frameWidth;
  _filename = filename;
  _passibilities = (Passibility *)calloc(
      sizeof(Passibility),
      getFrameCount()); // TODO: better c++ dynamic array? Also destructor
}
int TextureDef::getWidth() { return _width; }
int TextureDef::getHeight() { return _height; }
int TextureDef::getFrameHeight() { return _frameHeight; }
int TextureDef::getFrameWidth() { return _frameWidth; }
Rectf TextureDef::getFrameSize() {
  return Rectf(0.0f, 0.0f, getFrameWidth(), getFrameHeight());
}
std::string TextureDef::getFilename() { return _filename; }
gl::TextureRef TextureDef::useTexture() {

  if (_texture == nullptr && _shouldLoad) {
    filesystem::path texPath = _path / _filename;
    cout << "Loading texture: " << texPath << endl;
    try {
      _texture = gl::Texture::create(loadImage(texPath));
      _refCount++;
    }
    catch (...) {
      std::cout << std::endl << "unable to load the texture file!" << std::endl;
      _shouldLoad = false; // Prevent bad assets from reloading multiple times.
    }
  }

  return _texture;
}
void TextureDef::releaseTexture() { _refCount--; }
void TextureDef::setPath(filesystem::path path) { _path = path; }
filesystem::path TextureDef::getPath() { return _path; }

int TextureDef::getFrameCount() {
  int xFrames = _width / _frameWidth;
  int yFrames = _height / _frameHeight;
  return xFrames * yFrames;
}

Passibility TextureDef::getPassiblity(int frameNumber) {
  if (frameNumber < 0 || frameNumber >= getFrameCount()) {
    throw new std::exception(); // Out of bounds
  }
  return _passibilities[frameNumber];
}
void TextureDef::setPassiblity(int frameNumber, Passibility passability) {
  if (frameNumber < 0 || frameNumber >= getFrameCount()) {
    throw new std::exception(); // Out of bounds
  }
  _passibilities[frameNumber] = passability;
  _passabilityMap[passability.getInternalValue()] = frameNumber;
}

int TextureDef::getFrameFromPassibility(Passibility passability) {
  int val = passability.getInternalValue();
  if (_passabilityMap.count(val)) {
    return _passabilityMap[val];
  }
  return 0;
}

std::shared_ptr<TextureDef> TextureDef::FromYamlNode(YAML::Node node) {
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
  TextureDef *textureDef =
      new TextureDef(id, width, height, frameHeight, frameWidth, source);

  if (node["passibility"]) {
    // cout << "passibility node detected..." << endl;
    Node pRef = node["passibility"];
    // cout << "pRef: " << pRef << endl;
    // TODO: Code to parse passibility
    for (int i = 0; i < textureDef->getFrameCount(); i++) {
      if (pRef[i]) {
        Passibility p = pRef[i].as<Passibility>();
        textureDef->setPassiblity(i, p);
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

  return TextureDefRef(textureDef);
}
//
//  TextureDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 25/03/2014.
//
//

#include "TextureDef.h"
using namespace std;

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
gl::Texture *TextureDef::useTexture() {

  if (_texture == nullptr && _shouldLoad) {
    filesystem::path texPath = _path / _filename;
    cout << "Loading texture: " << texPath << endl;
    try {
      static gl::Texture newTex = gl::Texture(loadImage(texPath));
      _texture = &newTex;
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

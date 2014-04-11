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
TextureDef::TextureDef(int width, int height, int frameHeight, int frameWidth,
                       string source) {
  setValues(width, height, frameHeight, frameWidth, source);
};
void TextureDef::setValues(int width, int height, int frameHeight,
                           int frameWidth, string source) {
  _width = width;
  _height = height;
  _frameHeight = frameHeight;
  _frameWidth = frameWidth;
  _source = source;
  _passibilities = (Passibility *)calloc(
      sizeof(Passibility),
      getFrameCount()); // TODO: better c++ dynamic array? Also destructor
};

int TextureDef::getWidth() {
  return _width;
};
int TextureDef::getHeight() {
  return _height;
};
int TextureDef::getFrameHeight() {
  return _frameHeight;
};
int TextureDef::getFrameWidth() {
  return _frameWidth;
};
std::string TextureDef::getSource() {
  return _source;
};
gl::Texture TextureDef::useTexture() {

  if (_texture == nullptr) {
    filesystem::path texPath = _path / _source;
    cout << "Loading texture: " << texPath;
    static gl::Texture newTex = gl::Texture(loadImage(texPath));
    _texture = &newTex;
  }

  _refCount++;
  return *_texture;
};
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
}

//
//  TextureDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 25/03/2014.
//
//

#include "TextureDef.h"
#include <stdexcept>

using namespace std;
using namespace YAML;

// Constructors/Destructors

TextureDef::TextureDef(int id, int width, int height, int frameHeight,
                       int frameWidth, float border)
    : AssetDefBaseT(id) {
  _width = width;
  _height = height;
  _frameHeight = frameHeight;
  _frameWidth = frameWidth;
  _border = border;
}

TextureDef::~TextureDef() {};

// Getters/Setters

int TextureDef::getWidth() { return _width; }

int TextureDef::getHeight() { return _height; }

int TextureDef::getFrameWidth() { return _frameWidth; }

int TextureDef::getFrameHeight() { return _frameHeight; }

Rectf TextureDef::getFrameSize() {
  return Rectf(0.0f, 0.0f, getFrameWidth(), getFrameHeight());
}

float TextureDef::getBorder() { return _border; }

int TextureDef::getFrameCount() {
  int xFrames = _width / _frameWidth;
  int yFrames = _height / _frameHeight;
  return xFrames * yFrames;
}

Rectf TextureDef::getFrameUvCoords(const int frameNumber) {
  int tileXCount = (this->getWidth() / this->getFrameWidth());
  int tileYCount = (this->getHeight() / this->getFrameHeight());
  int xIndex = frameNumber % tileXCount;
  int yIndex = frameNumber / tileYCount;
  float normalisedBorderX = this->getBorder() / this->getWidth();
  float normalisedBorderY = this->getBorder() / this->getHeight();
  Rectf r;
  r.x1 = (xIndex / (float)tileXCount) + normalisedBorderX;
  r.x2 = ((xIndex + 1) / (float)tileXCount) - normalisedBorderX;
  r.y1 = (yIndex / (float)tileYCount) + normalisedBorderY;
  r.y2 = ((yIndex + 1) / (float)tileYCount) - normalisedBorderY;
  return r;
}

AssetType TextureDef::getAssetType() { return GetAssetType<TextureDef>::value; }

// Methods

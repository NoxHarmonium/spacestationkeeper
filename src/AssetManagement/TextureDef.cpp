//
//  TextureDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 25/03/2014.
//
//

#include "TextureDef.h"
#include <stdexcept>
#include "Utils.h"

using namespace std;
using namespace YAML;

// Constructors/Destructors

TextureDef::TextureDef(Node node)
    : AssetDefBaseT(
          -1) { // TODO: ID isn't used and probably should be depricated
  // Load in values from YAML file.
  int id, width, height, frameHeight, frameWidth;
  string filename;
  float border = 0.0f;

  // cout << "Deserialising TextureDef..." << endl;

  Utils::parseNode<int>(&id, node, "id");
  Utils::parseNode<int>(&width, node, "width");
  Utils::parseNode<int>(&height, node, "height");
  Utils::parseNode<int>(&frameWidth, node, "frameHeight");
  Utils::parseNode<int>(&frameHeight, node, "frameHeight");
  Utils::parseNode<string>(&filename, node, "filename");
  Utils::parseNode<float>(&border, node, "border", false);

  this->_id = id;
  this->_width = width;
  this->_height = height;
  this->_frameHeight = frameHeight;
  this->_frameWidth = frameWidth;
  this->_border = border;
  this->_filename = filename;
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

std::string TextureDef::getFilename() { return _filename; }

float TextureDef::getBorder() { return _border; }

bool TextureDef::getIsAnimated() { return false; }

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

void TextureDef::loadAsset() {
  if (!assetLoaded() && _shouldLoad) {
    filesystem::path texPath = getPath() / getFilename();
    cout << "Loading texture: " << texPath << endl;
    try {
      gl::TextureRef texRef = gl::Texture::create(loadImage(texPath));
      setAssetPointer(texRef);
    }
    catch (const std::exception &e) {
      cout << "unable to load the texture file: " << e.what() << endl;
      _shouldLoad = false; // Prevent bad assets from reloading multiple times.
      throw AssetLoadException(&e);
    }
  }
}

void TextureDef::unloadAsset() {
  // shared_ptr will handle destruction if nothing else has
  // a reference
  setAssetPointer(nullptr);
}

// Static Methods

std::shared_ptr<TextureDef> TextureDef::FromYamlNode(YAML::Node node) {
  return make_shared<TextureDef>(node);
}

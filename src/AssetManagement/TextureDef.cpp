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
                       int frameWidth, string filename, bool canWalk,
                       float border)
    : AssetDefBaseT(id) {
  _width = width;
  _height = height;
  _frameHeight = frameHeight;
  _frameWidth = frameWidth;
  _filename = filename;
  _passibilities = vector<Passibility>(
      getFrameCount(),
      Passibility()); // Fill vector with empty Passibility objects.
  _canWalk = canWalk;
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

bool TextureDef::getCanWalk() { return _canWalk; }

float TextureDef::getBorder() { return _border; }

std::string TextureDef::getFilename() { return _filename; }

Passibility TextureDef::getPassiblity(int frameNumber) {
  if (frameNumber < 0 || frameNumber >= getFrameCount()) {
    throw out_of_range("The specified frame number is out of range: " +
                       to_string(frameNumber));
  }
  return _passibilities[frameNumber];
}
void TextureDef::setPassiblity(int frameNumber, Passibility passability) {
  if (frameNumber < 0 || frameNumber >= getFrameCount()) {
    throw out_of_range("The specified frame number is out of range." +
                       to_string(frameNumber));
  }
  _passibilities[frameNumber] = passability;
  _passabilityMap[passability.getInternalValue()] = frameNumber;
}

int TextureDef::getFrameFromPassibility(Passibility passability) {
  int val = passability.getInternalValue();
  if (_passabilityMap.count(val)) {
    return _passabilityMap[val];
  }
  cout << "Warning: Could not get frame number from passability: "
       << passability << " Returning 0..." << endl;
  return 0;
}

int TextureDef::getFrameCount() {
  int xFrames = _width / _frameWidth;
  int yFrames = _height / _frameHeight;
  return xFrames * yFrames;
}

AssetType TextureDef::getAssetType() { return GetAssetType<TextureDef>::value; }

// Methods

void TextureDef::loadAsset() {
  if (!assetLoaded() && _shouldLoad) {
    filesystem::path texPath = getPath() / _filename;
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

  // Load in values from YAML file.
  int id, width, height, frameHeight, frameWidth;
  string filename;
  bool canWalk;
  float border = 0.0f;

  // cout << "Deserialising TextureDef..." << endl;

  Utils::parseNode<int>(&id, node, "id");
  Utils::parseNode<int>(&width, node, "width");
  Utils::parseNode<int>(&height, node, "height");
  Utils::parseNode<int>(&frameWidth, node, "frameHeight");
  Utils::parseNode<int>(&frameHeight, node, "frameHeight");
  Utils::parseNode<string>(&filename, node, "filename");
  Utils::parseNode<bool>(&canWalk, node, "canWalk");
  Utils::parseNode<float>(&border, node, "border", false);

  TextureDef *textureDef = new TextureDef(
      id, width, height, frameHeight, frameWidth, filename, canWalk, border);

  // Passability is optional
  Node pNode = node["passibility"];
  bool passabilityDefined =
      Utils::getChildNode(&pNode, node, "passibility", false);
  if (passabilityDefined) {
    for (int i = 0; i < textureDef->getFrameCount(); i++) {
      if (pNode[i].IsDefined()) {
        Passibility p = pNode[i].as<Passibility>();
        textureDef->setPassiblity(i, p);
        // cout << "Passibility: (" << i << "): " << p << endl;
      }
    }
  }

  return TextureDefRef(textureDef);
}
//
//  TileDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 18/05/2014.
//
//

#include "TileDef.h"
#include "AssetDefConverters.h"

TileDef::TileDef(int id, int width, int height, int frameHeight, int frameWidth,
                 string filename, bool canWalk, float border)
    : TextureDef(id, width, height, frameHeight, frameWidth, border) {
  _filename = filename;
  _passibilities = vector<Passibility>(
      getFrameCount(),
      Passibility()); // Fill vector with empty Passibility objects.
  _canWalk = canWalk;
}

TileDef::~TileDef() {}

bool TileDef::getCanWalk() { return _canWalk; }

std::string TileDef::getFilename() { return _filename; }

Passibility TileDef::getPassiblity(int frameNumber) {
  if (frameNumber < 0 || frameNumber >= getFrameCount()) {
    throw out_of_range("The specified frame number is out of range: " +
                       to_string(frameNumber));
  }
  return _passibilities[frameNumber];
}
void TileDef::setPassiblity(int frameNumber, Passibility passability) {
  if (frameNumber < 0 || frameNumber >= getFrameCount()) {
    throw out_of_range("The specified frame number is out of range." +
                       to_string(frameNumber));
  }
  _passibilities[frameNumber] = passability;
  _passabilityMap[passability.getInternalValue()] = frameNumber;
}

int TileDef::getFrameFromPassibility(Passibility passability) {
  int val = passability.getInternalValue();
  if (_passabilityMap.count(val)) {
    return _passabilityMap[val];
  }
  cout << "Warning: Could not get frame number from passability: "
       << passability << " Returning 0..." << endl;
  return 0;
}

void TileDef::loadAsset() {
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

void TileDef::unloadAsset() {
  // shared_ptr will handle destruction if nothing else has
  // a reference
  setAssetPointer(nullptr);
}

// Static Methods

std::shared_ptr<TileDef> TileDef::FromYamlNode(YAML::Node node) {

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

  TileDef *tileDef = new TileDef(id, width, height, frameHeight, frameWidth,
                                 filename, canWalk, border);

  // Passability is optional
  Node pNode = node["passibility"];
  bool passabilityDefined =
      Utils::getChildNode(&pNode, node, "passibility", false);
  if (passabilityDefined) {
    for (int i = 0; i < tileDef->getFrameCount(); i++) {
      if (pNode[i].IsDefined()) {
        Passibility p = pNode[i].as<Passibility>();
        tileDef->setPassiblity(i, p);
        // cout << "Passibility: (" << i << "): " << p << endl;
      }
    }
  }

  return TileDefRef(tileDef);
}

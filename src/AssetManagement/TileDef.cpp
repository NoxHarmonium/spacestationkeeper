//
//  TileDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 18/05/2014.
//
//

#include "TileDef.h"
#include "AssetDefConverters.h"

TileDef::TileDef(Node node) : TextureDef(node) {
  bool canWalk;

  Utils::parseNode<bool>(&canWalk, node, "canWalk");

  this->_canWalk = canWalk;

  _passibilities = vector<Passibility>(
      this->getFrameCount(),
      Passibility()); // Fill vector with empty Passibility objects.

  // Passability is optional
  Node pNode = node["passibility"];
  bool passabilityDefined =
      Utils::getChildNode(&pNode, node, "passibility", false);
  if (passabilityDefined) {
    for (int i = 0; i < this->getFrameCount(); i++) {
      if (pNode[i].IsDefined()) {
        Passibility p = pNode[i].as<Passibility>();
        this->setPassiblity(i, p);
        // cout << "Passibility: (" << i << "): " << p << endl;
      }
    }
  }
}

TileDef::~TileDef() {}

bool TileDef::getCanWalk() { return _canWalk; }

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

bool TileDef::getIsAnimated() { return false; }

// Static Methods

std::shared_ptr<TileDef> TileDef::FromYamlNode(YAML::Node node) {
  return make_shared<TileDef>(node);
}

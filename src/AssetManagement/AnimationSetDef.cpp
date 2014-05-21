//
//  AnimationSetDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 19/05/2014.
//
//

#include "AnimationSetDef.h"
#include "Utils.h"

// Constructors/Destructors
AnimationSetDef::AnimationSetDef(Node node) : AssetDefBaseT(-1) {
  string defaultAnimation;
  Utils::parseNode<string>(&defaultAnimation, node, "defaultAnimation");

  this->_defaultAnimation = defaultAnimation;

  Node animations;
  bool passabilityDefined =
      Utils::getChildNode(&animations, node, "animations");
}

AnimationSetDef::~AnimationSetDef() {}

// Methods
void AnimationSetDef::loadAsset() {}

void AnimationSetDef::unloadAsset() {}

// Static Methods
std::shared_ptr<AnimationSetDef> AnimationSetDef::FromYamlNode(Node node) {
  return make_shared<AnimationSetDef>(node);
}

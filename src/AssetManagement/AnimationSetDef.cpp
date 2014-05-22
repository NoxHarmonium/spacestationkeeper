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
AnimationSetDef::AnimationSetDef(Node node)
    : AssetDefBaseT<AnimationSetMap>(-1) {
  string defaultAnimation;
  AnimationSetMapRef animationSet = make_shared<AnimationSetMap>();

  Utils::parseNode<string>(&defaultAnimation, node, "defaultAnimation");

  this->_defaultAnimation = defaultAnimation;

  Node animations;
  Utils::getChildNode(&animations, node, "animations");
  for (Node animation : animations) {
    string animationName;
    Utils::parseNode(&animationName, animation, "name");

    // Pass in root node so that animation definitions can extract common
    // texture data.
    AnimationDefRef animRef = AnimationDef::FromYamlNode(node, animationName);
    (*animationSet)[animationName] = animRef;
  }
  setAssetPointer(animationSet);
}

AnimationSetDef::~AnimationSetDef() {}

// Getters/Setters
string AnimationSetDef::getDefaultAnimation() { return _defaultAnimation; }

// Methods
void AnimationSetDef::loadAsset() {}

void AnimationSetDef::unloadAsset() {}

// Static Methods
std::shared_ptr<AnimationSetDef> AnimationSetDef::FromYamlNode(Node node) {
  return make_shared<AnimationSetDef>(node);
}

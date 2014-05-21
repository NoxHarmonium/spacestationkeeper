//
//  AnimationDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 21/05/2014.
//
//

#include "AnimationDef.h"
#include "Utils.h"

// Constructors/Destructors
AnimationDef::AnimationDef(Node node, string animationName) : TextureDef(node) {
  string name;
  int frameStart, frameEnd;
  float rate;
  bool loop;

  bool keyFound = false;
  Node animation, animations;
  Utils::getChildNode(&animations, node, "animations");

  if (!animations.IsSequence()) {
    throw AssetLoadException(
        AssetLoadException::AssetLoadExceptionReason::AssetDefInvalidFormat,
        "The animations node should be a list of animation nodes.");
  }

  for (Node n : animations) {
    Utils::parseNode<string>(&name, animation, "name");
    if (name == animationName) {
      animation = n;
      keyFound = true;
      break;
    }
  }

  if (!keyFound) {
    throw AssetLoadException(
        AssetLoadException::AssetLoadExceptionReason::AssetDefMissingKey,
        "animationName");
  }

  Utils::parseNode<int>(&frameStart, animation, "frameStart");
  Utils::parseNode<int>(&frameEnd, animation, "frameEnd");
  Utils::parseNode<float>(&rate, animation, "rate");
  Utils::parseNode<bool>(&loop, animation, "loop");

  this->_name = name;
  this->_frameStart = frameStart;
  this->_frameEnd = frameEnd;
  this->_rate = rate;
  this->_loop = loop;
}

AnimationDef::~AnimationDef() {}

// Getters/Setters
string AnimationDef::getName() { return _name; }

int AnimationDef::getFrameStart() { return _frameStart; }

int AnimationDef::getFrameEnd() { return _frameEnd; }

float AnimationDef::getRate() { return _rate; }

bool AnimationDef::getLoop() { return _loop; }

bool AnimationDef::getIsAnimated() { return true; }

// Static Methods
std::shared_ptr<AnimationDef> AnimationDef::FromYamlNode(Node node,
                                                         string animationName) {
  return make_shared<AnimationDef>(node, animationName);
}
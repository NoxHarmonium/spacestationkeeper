//
//  AnimatedSprite.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 25/05/2014.
//
//

#include "AnimatedSprite.h"
#include <math.h>
#include "ComponentDrivenApp.h"

// Constructors/Destructors
AnimatedSprite::AnimatedSprite() : Sprite() {
  reset();
  // cout << "!!Constructor: AnimatedSprite::AnimatedSprite()" << endl;
  serialiseField("animationSet", "AnimationSetDef", "getAnimationSet",
                 "setAnimationSet");
  serialiseField("animationName", "string", "getAnimationName",
                 "setAnimationName");
  serialiseField("playing", "bool", "getPlaying", "setPlaying", false);
};

AnimatedSprite::~AnimatedSprite() {}

// Getters/Setters
AnimationSetDefRef AnimatedSprite::getAnimationSet() {
  return _currentAnimationSet;
}

void AnimatedSprite::setAnimationSet(AnimationSetDefRef animationSet) {
  _currentAnimationSet = animationSet;
  loadAnimation();
}

string AnimatedSprite::getAnimationName() { return _currentAnimationName; }

void AnimatedSprite::setAnimationName(string animationName) {
  _currentAnimationName = animationName;
  loadAnimation();
}

float AnimatedSprite::getFrameRate() { return _frameRate; }

void AnimatedSprite::setFrameRate(float rate) { _frameRate = rate; }

bool AnimatedSprite::getLoop() { return _loop; }

void AnimatedSprite::setLoop(bool loop) { _loop = loop; }

bool AnimatedSprite::getPlaying() { return _playing; }

void AnimatedSprite::setPlaying(bool playing) { _playing = playing; }

// Methods
void AnimatedSprite::reset() {
  _currentFrame = 0;
  _playing = false;
  _t = 0;
  updateSprite();
}

void AnimatedSprite::play() {
  _playing = true;
  updateSprite();
}

void AnimatedSprite::stop() { _playing = false; }

void AnimatedSprite::setup() { Sprite::setup(); }

void AnimatedSprite::update(float deltaTime) {
  if (_playing && _currentAnimation != nullptr) {
    _t += deltaTime;
    _currentFrame = (int)floor(_t * (float)_frameRate);
    if (_currentFrame > _currentAnimation->getFrameEnd()) {
      if (_loop) {
        _currentFrame = 0;
        _t = 0.0f;
      } else {
        stop();
      }
    }
    updateSprite();
  }
}

void AnimatedSprite::updateSprite() {
  setSpriteTexture(dynamic_pointer_cast<TextureDef>(_currentAnimation));
  setSpriteFrame(_currentFrame);
}

void AnimatedSprite::loadAnimation() {
  if (_currentAnimationSet != nullptr) {
    AnimationSetMapRef animMap = _currentAnimationSet->getAsset();
    string defaultAnim = _currentAnimationSet->getDefaultAnimation();
    if (animMap->count(_currentAnimationName) == 0) {
      if (animMap->count(defaultAnim) == 0) {
        cout << "Warning: Could not load default animation: " + defaultAnim;
        _currentAnimation = nullptr;
      }
      _currentAnimation = (*animMap)[defaultAnim];
    } else {
      _currentAnimation = (*animMap)[_currentAnimationName];
    }
    _frameRate = _currentAnimation->getRate();
    _loop = _currentAnimation->getLoop();
  }
  updateSprite();
}
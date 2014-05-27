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
AnimatedSprite::AnimatedSprite() : Sprite() {};

AnimatedSprite::AnimatedSprite(AnimationSetDefRef animationSet) : Sprite() {
  setAnimationSet(animationSet);
}

AnimatedSprite::AnimatedSprite(AnimationSetDefRef animationSet,
                               string animationName)
    : Sprite() {
  setAnimationSet(animationSet);
  setAnimationName(animationName);
}

AnimatedSprite::~AnimatedSprite() {}

// Getters/Setters
AnimationSetDefRef AnimatedSprite::getAnimationSet() {
  return _currentAnimationSet;
}

void AnimatedSprite::setAnimationSet(AnimationSetDefRef animationSet) {
  _currentAnimationSet = animationSet;
}

string AnimatedSprite::getAnimationName() { return _currentAnimationName; }

void AnimatedSprite::setAnimationName(string animationName) {
  _currentAnimationName = animationName;
  reset();
}

float AnimatedSprite::getFrameRate() { return _frameRate; }

void AnimatedSprite::setFrameRate(float rate) { _frameRate = rate; }

bool AnimatedSprite::getLoop() { return _loop; }

void AnimatedSprite::setLoop(bool loop) { _loop = loop; }

// Methods
void AnimatedSprite::reset() {
  _currentFrame = 0;
  _playing = false;
  _t = 0;
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

void AnimatedSprite::play() {
  _playing = true;
  updateSprite();
}

void AnimatedSprite::stop() { _playing = false; }

void AnimatedSprite::setup() {}

void AnimatedSprite::update() {
  if (_playing && _currentAnimation != nullptr) {
    float delta = ComponentDrivenApp::Instance()->getDeltaTime();
    _t += delta;
    _currentFrame = (int)floor(_t / _frameRate);
    if (_currentFrame > _currentAnimation->getFrameEnd()) {
      if (_loop) {
        _currentFrame = 0;
      } else {
        stop();
      }
    }
    updateSprite();
  }
}

void AnimatedSprite::updateSprite() {
  setSpriteTexture(static_pointer_cast<TextureDef>(_currentAnimation));
  setSpriteFrame(_currentFrame);
}
//
//  AnimatedSprite.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 25/05/2014.
//
//

#ifndef SpaceStationKeeper_AnimatedSprite_h
#define SpaceStationKeeper_AnimatedSprite_h

#include "Sprite.h"
#include "AnimationDef.h"
#include "AnimationSetDef.h"

class AnimatedSprite : public Sprite {
public:
  // Constructors/Destructors
  AnimatedSprite();
  AnimatedSprite(AnimationSetDefRef animation);
  AnimatedSprite(AnimationSetDefRef animation, string animationName);
  virtual ~AnimatedSprite();

  // Getters/Setters
  AnimationSetDefRef getAnimationSet();
  void setAnimationSet(AnimationSetDefRef animationSet);
  string getAnimationName();
  void setAnimationName(string animationName);
  float getFrameRate();
  void setFrameRate(float rate);
  bool getLoop();
  void setLoop(bool loop);

  // Methods
  void reset();
  void play();
  void stop();

  virtual void setup() override;
  virtual void update() override;

private:
  // Methods
  void updateSprite();

  // Fields
  float _t;
  bool _loop;
  AnimationSetDefRef _currentAnimationSet = nullptr;
  string _currentAnimationName = nullptr;
  AnimationDefRef _currentAnimation = nullptr;
  int _currentFrame;
  float _frameRate;
  bool _playing;
};

typedef std::shared_ptr<AnimatedSprite> AnimatedSpriteRef;

#endif

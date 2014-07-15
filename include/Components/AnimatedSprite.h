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

namespace BlazeEngine {
namespace Components {

class AnimatedSprite : public Sprite {
public:
  // Constructors/Destructors
  AnimatedSprite();
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
  bool getPlaying();
  void setPlaying(bool playing);

  // Methods
  void reset();
  void play();
  void stop();

  virtual void setup() override;
  virtual void update(float deltaTime) override;

private:
  // Methods
  void updateSprite();
  void loadAnimation();

  // Fields
  float _t;
  bool _loop;
  AnimationSetDefRef _currentAnimationSet;
  string _currentAnimationName;
  AnimationDefRef _currentAnimation;
  int _currentFrame;
  float _frameRate;
  bool _playing;
};

typedef std::shared_ptr<AnimatedSprite> AnimatedSpriteRef;
}
}

#endif

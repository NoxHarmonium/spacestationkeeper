//
//  HighlightTileOnMouseOver.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 13/04/2014.
//
//

#ifndef SpaceStationKeeper_HighlightTileOnMouseOver_cpp
#define SpaceStationKeeper_HighlightTileOnMouseOver_cpp

#include "pch.h"
#include "Behaviour.h"

class HighlightBehaviour : public Behaviour {
public:
  HighlightBehaviour(GameComponent *component,
                     float brightnessMultiplier = 1.5f,
                     ColorAf baseColorMultiplier = ColorAf(1.0f, 1.0f, 1.0f,
                                                           1.0f));
  ~HighlightBehaviour() {};

  void begin();
  void update(float deltaT);
  void end();
  vector<Modifier *> getModifiers();

  bool hasBegun();

private:
  bool _hasBegun = false;
  float _elapsedTime = 0.0f;
  float _brightnessMultiplier;
  ColorAf _baseColorMultiplier;
  ;
};

#endif

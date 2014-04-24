//
//  HighlightTileOnMouseOver.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 13/04/2014.
//
//

#ifndef SpaceStationKeeper_HighlightTileOnMouseOver_cpp
#define SpaceStationKeeper_HighlightTileOnMouseOver_cpp

#include "Behaviour.h"

class HighlightBehaviour : public Behaviour {
public:
  HighlightBehaviour(RenderComponent *component,
                     float brightnessModifier = 1.5f,
                     ColorAf colorModifier = ColorAf(1.0f, 1.0f, 1.0f, 1.0f));

  void Begin();
  void Update(float deltaT);
  void End();

  bool hasBegun();

private:
  bool _hasBegun = false;
  float _elapsedTime = 0.0f;
  float _brightnessModifier;
  // TODO: Implement pipeline so that behaviour modifications don't persist
  float _originalBrightness;
  ColorAf _originalColor;
  ColorAf _colorModifier;
  ;
};

#endif

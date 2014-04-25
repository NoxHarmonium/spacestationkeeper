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
                     float brightnessMultiplier = 1.5f,
                     ColorAf baseColorMultiplier = ColorAf(1.0f, 1.0f, 1.0f,
                                                           1.0f));

  void Begin();
  void Update(float deltaT);
  void End();
  void ApplyModifications(TransformModifier *transformModifier,
                          MaterialModifier *materialModifier);

  bool hasBegun();

private:
  bool _hasBegun = false;
  float _elapsedTime = 0.0f;
  float _brightnessMultiplier;
  ColorAf _baseColorMultiplier;
  ;
};

#endif

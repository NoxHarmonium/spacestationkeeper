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
  HighlightBehaviour(RenderComponent *component);

  void Begin();
  void Update(float deltaT);
  void End();

  bool hasBegun();

private:
  bool _hasBegun = false;
  float _elapsedTime = 0.0f;
};

#endif

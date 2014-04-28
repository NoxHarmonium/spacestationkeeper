//
//  RotationModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_RotateModifier_h
#define SpaceStationKeeper_RotateModifier_h

#include "Modifier.h"

class RotateModifier : public Modifier {
public:
  RotateModifier(Quatf rotation) : _rotation(rotation) {};
  ~RotateModifier() {};

  void apply(RenderInfo *renderInfo);

private:
  Quatf _rotation;
};

#endif

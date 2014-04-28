//
//  ScaleModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_ScaleModifier_h
#define SpaceStationKeeper_ScaleModifier_h

#include "Modifier.h"

class ScaleModifier : public Modifier {
public:
  ScaleModifier(Vec3f scale) : _scale(scale) {};
  ~ScaleModifier() {};

  void apply(RenderInfo *renderInfo);

private:
  Vec3f _scale;
};

#endif

//
//  TranslateModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_TranslateModifier_h
#define SpaceStationKeeper_TranslateModifier_h

#include "Modifier.h"

class TranslateModifier : public Modifier {
public:
  TranslateModifier(Vec3f translation) : _translation(translation) {};
  ~TranslateModifier() {};

  void apply(RenderInfo *renderInfo);

private:
  Vec3f _translation;
};

#endif

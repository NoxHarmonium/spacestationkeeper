//
//  BrightnessModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_BrightnessModifier_h
#define SpaceStationKeeper_BrightnessModifier_h

#include "Modifier.h"

class BrightnessModifier : public Modifier {
public:
  BrightnessModifier(float factor, ModifyMode mode = ModifyMode::Add)
      : _factor(factor), _mode(mode) {};
  ~BrightnessModifier() {};

  void apply(RenderInfo *renderInfo);

private:
  float _factor;
  ModifyMode _mode;
};

#endif

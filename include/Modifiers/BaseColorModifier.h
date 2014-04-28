//
//  BaseColorModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_BaseColorModifier_h
#define SpaceStationKeeper_BaseColorModifier_h

#include "Modifier.h"

class BaseColorModifier : public Modifier {
public:
  BaseColorModifier(ColorAf factor, ModifyMode mode = ModifyMode::Add)
      : _factor(factor), _mode(mode) {};
  ~BaseColorModifier() {};

  void apply(RenderInfo *renderInfo);

private:
  ColorAf _factor;
  ModifyMode _mode;
};

#endif

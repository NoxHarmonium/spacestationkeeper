//
//  Modifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_Modifier_h
#define SpaceStationKeeper_Modifier_h

#include "RenderInfo.h"

enum ModifyMode { Add = 0, Multiply = 1 };

class Modifier {
public:
  virtual void apply(RenderInfo *renderinfo) = 0;
  virtual ~Modifier() {};
};

#endif

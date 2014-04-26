//
//  Trigger.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#ifndef SpaceStationKeeper_Trigger_h
#define SpaceStationKeeper_Trigger_h

#include <stdlib.h>
#include "Behaviour.h"
#include "GameComponent.h"

class Trigger {
public:
  virtual bool isActive(GameComponent *gameComponent) = 0;
};

#endif

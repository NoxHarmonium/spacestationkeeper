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
#include "RenderComponent.h"

class Trigger {
public:
  virtual void RegisterBehaviour(RenderComponent *target,
                                 Behaviour *behaviour) = 0;
};

#endif

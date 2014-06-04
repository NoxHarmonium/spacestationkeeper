//
//  BotBehaviourWrapper.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/06/2014.
//
//

#ifndef SpaceStationKeeper_BotBehaviourWrapper_h
#define SpaceStationKeeper_BotBehaviourWrapper_h

#include "BotBehaviour.h"

struct BotBehaviourWrapper : public BotBehaviour, public luabind::wrap_base {
  BotBehaviourWrapper() : BotBehaviour(), luabind::wrap_base() {}

  // Call registers
  virtual Vec3f getForce(BotRef bot) override {
    return call<Vec3f>("getForce", bot);
  };
};

#endif

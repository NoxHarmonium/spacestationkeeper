//
//  BotWrapper.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/05/2014.
//
//

#ifndef SpaceStationKeeper_BotWrapper_h
#define SpaceStationKeeper_BotWrapper_h

#include "Bot.h"

struct BotWrapper : public Bot, public luabind::wrap_base {
  BotWrapper() : Bot() {}
  // Call registers
  virtual Vec2i getDestination() override {
    return call<Vec2i>("getDestination");
  };

  virtual float getSpeed() override {
    return call<float>("getSpeed");
  };

  virtual bool willAcceptJob(JobRef job) override {
    return call<bool>("willAcceptJob");
  };

  virtual void acceptJob(JobRef job) override {
    call<void>("acceptJob", job);
  };

  virtual void update() override {
    call<void>("update");
  };
};

#endif

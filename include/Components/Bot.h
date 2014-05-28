//
//  Bot.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/05/2014.
//
//

#ifndef SpaceStationKeeper_Bot_h
#define SpaceStationKeeper_Bot_h

#include <memory>
#include "Job.h"
#include "GameComponent.h"

using namespace ci;

class Bot : public GameComponent {

public:
  // Constructors/Destructors
  Bot() {}
  virtual ~Bot() {}

  // Getters/Setters
  virtual Vec2i getDestination() = 0;
  virtual float getSpeed() = 0;
  virtual bool willAcceptJob(JobRef job) = 0;
  virtual void acceptJob(JobRef job) = 0;
  virtual void update(float deltaTime) override = 0;
};

typedef std::shared_ptr<Bot> BotRef;

#endif

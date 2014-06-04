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
#include <set>
#include "BotBehaviour.h"

typedef list<Vec2i> CoordList;
typedef std::shared_ptr<CoordList> CoordListRef;

using namespace ci;

class Bot : public GameComponent {

public:
  enum BotState { WaitingForJob = 0, MovingToJob = 1, Working = 2 };

  // Constructors/Destructors
  Bot() {}
  virtual ~Bot() {}

  // Getters/Setters
  virtual Vec2i getCoord() = 0;
  virtual Vec2i getDestination() = 0;
  virtual float getSpeed() = 0;
  virtual bool canAcceptJobs() = 0;
  virtual bool willAcceptJob(JobRef job) = 0;
  virtual void acceptJob(JobRef job) = 0;
  virtual JobRef getCurrentJob() = 0;
  virtual BotState getState() = 0;
  virtual void setup() override = 0;
  virtual void update(float deltaTime) override = 0;

  void addBehaviour(BotBehaviourRef behaviour);
  void removeBehaviour(BotBehaviourRef behaviour);
  set<BotBehaviourRef> getBehaviours();

private:
  set<BotBehaviourRef> _behaviours;
};

typedef std::shared_ptr<Bot> BotRef;

#endif

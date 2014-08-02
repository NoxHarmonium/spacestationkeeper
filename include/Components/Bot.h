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
#include "GameObject.h"
#include <set>
#include "BotBehaviour.h"
#include "SteeringTarget.h"

namespace BlazeEngine {
namespace Components {

using namespace ci;
using namespace BlazeEngine::Jobs;
using namespace AI::Steering;

class Bot : public GameComponent, public SteeringTarget {

public:
  enum BotState { WaitingForJob = 0, MovingToJob = 1, Working = 2 };

  // Constructors/Destructors
  Bot();
  virtual ~Bot();

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

  RenderableRef getRenderableRef() override;

private:
  set<BotBehaviourRef> _behaviours;
};

typedef std::shared_ptr<Bot> BotRef;

// Needed for Lua to compare instances
bool operator==(const Bot &a, const Bot &b);
// Needed for Lua to print address
std::ostream &operator<<(std::ostream &lhs, const Bot &rhs);
}
}

#endif

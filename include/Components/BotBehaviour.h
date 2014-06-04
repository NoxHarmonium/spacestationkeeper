//
//  BotBehaviour.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/06/2014.
//
//

#ifndef SpaceStationKeeper_BotBehaviour_h
#define SpaceStationKeeper_BotBehaviour_h

#include <memory>

// Forward Decs
class Bot;
typedef std::shared_ptr<Bot> BotRef;

using namespace ci;

class BotBehaviour {
public:
  BotBehaviour() {}
  virtual ~BotBehaviour() {}

  virtual Vec3f getForce(BotRef bot) = 0;
};

typedef std::shared_ptr<BotBehaviour> BotBehaviourRef;

#endif

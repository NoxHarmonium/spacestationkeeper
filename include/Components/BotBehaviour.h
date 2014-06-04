//
//  BotBehaviour.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/06/2014.
//
//

#ifndef SpaceStationKeeper_BotBehaviour_h
#define SpaceStationKeeper_BotBehaviour_h

using namespace ci;

class BotBehaviour {
public:
  virtual Vec3f getForce() = 0;
};

typedef std::shared_ptr<BotBehaviour> BotBehaviourRef;

#endif

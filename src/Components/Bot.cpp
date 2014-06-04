//
//  Bot.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/06/2014.
//
//

#include "Bot.h"

void Bot::addBehaviour(BotBehaviourRef behaviour) {
  _behaviours.insert(behaviour);
}

void Bot::removeBehaviour(BotBehaviourRef behaviour) {
  _behaviours.erase(behaviour);
}

set<BotBehaviourRef> Bot::getBehaviours() {
  return _behaviours;
  // TODO: Can I just return an iterator so access to internal set is not
  // exposed?
}
//
//  Bot.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/06/2014.
//
//

#include "Bot.h"

namespace BlazeEngine {
namespace Components {

// Methods

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

// Operators

bool operator==(const Bot &a, const Bot &b) { return &a == &b; }
std::ostream &operator<<(std::ostream &lhs, const Bot &rhs) {
  lhs << &rhs;
  return lhs;
}
}
}

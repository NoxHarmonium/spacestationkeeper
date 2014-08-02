//
//  Bot.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/06/2014.
//
//

#include "Bot.h"
#include <memory>

namespace BlazeEngine {
namespace Components {

// Methods

Bot::Bot() : GameComponent(), SteeringTarget() {}

Bot::~Bot() {}

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

// Overrides

RenderableRef Bot::getRenderableRef() {
  if (this->gameObject == nullptr) {
    return nullptr;
  }
  return std::dynamic_pointer_cast<Renderable>(this->gameObject);
}

// Operators

bool operator==(const Bot &a, const Bot &b) { return &a == &b; }
std::ostream &operator<<(std::ostream &lhs, const Bot &rhs) {
  lhs << &rhs;
  return lhs;
}
}
}

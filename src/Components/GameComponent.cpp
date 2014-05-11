//
//  GameComponent.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "GameObject.h"
#include "GameComponent.h"
#include <boost/uuid/uuid_io.hpp>

GameComponent::GameComponent() { setId(to_string(_uuidGenerator())); }

GameComponent::GameComponent(string id) : _id(id) {}

string GameComponent::getId() { return _id; }

void GameComponent::setId(string id) {
  if (gameObject != nullptr) {
    gameObject->reassignId(this, id);
  }
  _id = id;
}

boost::uuids::random_generator GameComponent::_uuidGenerator =
    boost::uuids::random_generator();

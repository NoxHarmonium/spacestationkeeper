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

GameComponent::GameComponent() { _id = to_string(_uuidGenerator()); }

GameComponent::GameComponent(string id) : _id(id) {}

string GameComponent::getId(std::shared_ptr<GameComponent> component) {
  return component->_id;
}

void GameComponent::setId(std::shared_ptr<GameComponent> component, string id) {
  if (component->gameObject != nullptr) {
    component->gameObject->reassignId(component, id);
  }
  component->_id = id;
}

boost::uuids::random_generator GameComponent::_uuidGenerator =
    boost::uuids::random_generator();

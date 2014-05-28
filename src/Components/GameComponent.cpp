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

GameComponent::GameComponent() {
  _id = to_string(_uuidGenerator());
  _serialisedFields = make_shared<SerialisedFieldList>();
}

GameComponent::GameComponent(string id) : _id(id) {}

SerialisedFieldListRef GameComponent::getSerialisedFields() {
  return _serialisedFields;
}

void GameComponent::serialiseField(string name, string type) {
  cout << "GameComponent::serialiseField: name: " << name << " type: " << type
       << endl;
  _serialisedFields->push_back(make_shared<SerialisedField>(name, type, true));
}

void GameComponent::serialiseField(string name, string type, bool required) {
  cout << "GameComponent::serialiseField: name: " << name << " type: " << type
       << endl;
  _serialisedFields->push_back(
      make_shared<SerialisedField>(name, type, required));
}

void GameComponent::serialiseField(string name, string type, string getterName,
                                   string setterName) {
  cout << "GameComponent::serialiseField: name: " << name << " type: " << type
       << " getterName: " << getterName << " setterName: " << setterName
       << endl;
  _serialisedFields->push_back(
      make_shared<SerialisedField>(name, type, getterName, setterName, true));
}

void GameComponent::serialiseField(string name, string type, string getterName,
                                   string setterName, bool required) {
  cout << "GameComponent::serialiseField: name: " << name << " type: " << type
       << " getterName: " << getterName << " setterName: " << setterName
       << endl;
  _serialisedFields->push_back(make_shared<SerialisedField>(
      name, type, getterName, setterName, required));
}

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

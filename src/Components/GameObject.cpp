//
//  GameObject.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#include "GameObject.h"
#include <stdexcept>
#include <boost/uuid/uuid_io.hpp>

// Constructors/Destructors
GameObject::GameObject() {
  _id = to_string(_uuidGenerator());
  renderer = make_shared<RenderInfo>();
  _bindingManager = BindingManager::Instance();
}

GameObject::~GameObject() {}

void GameObject::addComponent(GameComponentRef component) {
  string id = GameComponent::getId(component);
  checkIdValidity(id);
  _componentMap[id] = component;
  component->gameObject = this; // TODO: Encapsulate more? i.e. setGameObject()?
  _componentListDirty = true;
  _setupQueue.push_back(component);
}

void GameObject::removeComponent(GameComponentRef component) {
  _componentMap.erase(GameComponent::getId(component));
  component->gameObject = nullptr; // End null reference
  _componentListDirty = true;
}

GameComponentRef GameObject::getComponent(string id) {
  if (_componentMap.count(id) == 0) {
    throw runtime_error("No component found for id: " + id);
  }
  return _componentMap[id];
}

void GameObject::refreshComponentList() {
  if (_componentListDirty) {
    componentList.clear();
    // Generate a vector that lua can iterate through because I'm not sure how
    // to get it to support maps yet.
    for (auto &kvp : _componentMap) {
      componentList.push_back(kvp.second);
    }
    _componentListDirty = false;
  }
}

void GameObject::reassignId(GameComponentRef component, string newId) {
  // This method exists because calling remove and then add again may cause some
  // unwanted logic to fire
  // when more functionallity is implemented
  checkIdValidity(newId);
  _componentMap.erase(GameComponent::getId(component));
  _componentMap[GameComponent::getId(component)] = component;
}

RenderInfoRef GameObject::getRenderer() { return renderer; }

string GameObject::getId() { return _id; }
void GameObject::setId(string id) { _id = id; }

//! Forwards event to component to perform any application cleanup before
// exiting.
void GameObject::shutdown() {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled &&
        _bindingManager->catchLuaExceptions([comp]() { comp->shutdown(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}

//! Forwards event to component to perform any once-per-loop computation.
void GameObject::update() {

  // Make sure that new objects get set up properly
  // Setup() could be called when the component is added but it is better for it
  // to be dispached in the main flow for compatibility with later features.
  for (auto &comp : _setupQueue) {
    if (_bindingManager->catchLuaExceptions([comp]() { comp->setup(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
      return;
    };
  }
  _setupQueue.clear();

  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled &&
        _bindingManager->catchLuaExceptions([comp]() { comp->update(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to perform any rendering once-per-loop or in
// response to
// OS-prompted requests for refreshes.
void GameObject::draw() {
  // Perform automatic GO rendering
  renderer->draw();

  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled &&
        _bindingManager->catchLuaExceptions([comp]() { comp->draw(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}

//! Forwards event to component to receive mouse-down events.
void GameObject::mouseDown(MouseEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->mouseDown(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to receive mouse-up events.
void GameObject::mouseUp(MouseEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->mouseUp(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to receive mouse-wheel events.
void GameObject::mouseWheel(MouseEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->mouseWheel(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to receive mouse-move events.
void GameObject::mouseMove(MouseEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->mouseMove(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to receive mouse-drag events.
void GameObject::mouseDrag(MouseEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->mouseDrag(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}

//! Forwards event to component to respond to the beginning of a multitouch
// sequence
void GameObject::touchesBegan(TouchEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->touchesBegan(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to respond to movement (drags) during a
// multitouch sequence
void GameObject::touchesMoved(TouchEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->touchesMoved(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to respond to the end of a multitouch sequence
void GameObject::touchesEnded(TouchEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->touchesEnded(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}

//! Forwards event to component to receive key-down events.
void GameObject::keyDown(KeyEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->keyDown(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to receive key-up events.
void GameObject::keyUp(KeyEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->keyUp(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to receive window resize events.
void GameObject::resize() {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled &&
        _bindingManager->catchLuaExceptions([comp]() { comp->resize(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to receive file-drop events.
void GameObject::fileDrop(FileDropEvent event) {
  for (auto &kvp : getRegisteredComponentsCopy()) {
    GameComponentRef comp = kvp.second;
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->fileDrop(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}

map<string, GameComponentRef> GameObject::getRegisteredComponentsCopy() {
  return map<string, GameComponentRef>(_componentMap);
}

void GameObject::checkIdValidity(string id) {
  if (id.length() == 0) {
    throw runtime_error("An ID is required for GameComponent objects.");
  }
  if (_componentMap.count(id) > 0) {
    throw runtime_error(
        "The component ID: " + id +
        " already exists on this gameObject. A unique ID is required.");
  }
}

boost::uuids::random_generator GameObject::_uuidGenerator =
    boost::uuids::random_generator();

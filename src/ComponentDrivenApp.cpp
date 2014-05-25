//
//  ComponentDrivenApp.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "ComponentDrivenApp.h"
#include "GameObject.h"
#include "yaml-cpp/yaml.h"
#include "Utils.h"
#include "GameObject.h"
#include "ScriptDef.h"

using namespace YAML;
using namespace boost;

ComponentDrivenApp::ComponentDrivenApp() {
  assert(_instance == nullptr);
  _instance = this;
  _bindingManager = BindingManager::Instance();
}

ComponentDrivenApp::~ComponentDrivenApp() {}

ComponentDrivenApp *ComponentDrivenApp::Instance() { return _instance; }

//! Registers a component to receive app events
void ComponentDrivenApp::registerGameObject(GameObjectRef gameObject) {
  if (_registeredGameObjects.count(gameObject)) {
    throw runtime_error("This gameObject is already registered.");
  }
  _registeredGameObjects.insert(gameObject);
}

void ComponentDrivenApp::destroyGameObject(GameObjectRef gameObject) {
  _registeredGameObjects.erase(gameObject);
}

//! Get a list of currently registered components
set<GameObjectRef> ComponentDrivenApp::getGameObjects() {
  return this->_registeredGameObjects;
}

//! Forwards event to component to perform any application cleanup before
// exiting.
void ComponentDrivenApp::shutdown() {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->shutdown();
  }
}

//! Forwards event to component to perform any once-per-loop computation.
void ComponentDrivenApp::update() {
  if (!isnan(_lastElapsedTime)) {
    _deltaTime = ci::app::getElapsedSeconds() - _lastElapsedTime;
  }
  _lastElapsedTime = ci::app::getElapsedSeconds();

  if (_jobManager != nullptr) {
    std::shared_ptr<JobManager> jobMan =
        _jobManager; // Need to make local copy for lambda capture
    _bindingManager->catchLuaExceptions([jobMan]() { jobMan->update(); });
  }

  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->update();
  }
}
//! Forwards event to component to perform any rendering once-per-loop or in
// response to
// OS-prompted requests for refreshes.
void ComponentDrivenApp::draw() {
  // z-depth sorting // TODO: Make more efficient
  set<GameObjectRef> gameObjects = getRegisteredGameObjectsCopy();

  // Copy set into vector
  std::vector<GameObjectRef> vector =
      std::vector<GameObjectRef>(gameObjects.begin(), gameObjects.end());

  // Depth sort the vector
  sort(std::begin(vector), std::end(vector),
       [](GameObjectRef a, GameObjectRef b) {
    return b->renderer->transform->localPosition.z >
           a->renderer->transform->localPosition.z;
  });

  // Draw in order
  for (auto &comp : vector) {
    comp->draw();
  }
}

//! Forwards event to component to receive mouse-down events.
void ComponentDrivenApp::mouseDown(MouseEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->mouseDown(event);
  }
}
//! Forwards event to component to receive mouse-up events.
void ComponentDrivenApp::mouseUp(MouseEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->mouseUp(event);
  }
}
//! Forwards event to component to receive mouse-wheel events.
void ComponentDrivenApp::mouseWheel(MouseEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->mouseWheel(event);
  }
}
//! Forwards event to component to receive mouse-move events.
void ComponentDrivenApp::mouseMove(MouseEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->mouseMove(event);
  }
}
//! Forwards event to component to receive mouse-drag events.
void ComponentDrivenApp::mouseDrag(MouseEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->mouseDrag(event);
  }
}

//! Forwards event to component to respond to the beginning of a multitouch
// sequence
void ComponentDrivenApp::touchesBegan(TouchEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->touchesBegan(event);
  }
}
//! Forwards event to component to respond to movement (drags) during a
// multitouch sequence
void ComponentDrivenApp::touchesMoved(TouchEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->touchesMoved(event);
  }
}
//! Forwards event to component to respond to the end of a multitouch sequence
void ComponentDrivenApp::touchesEnded(TouchEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->touchesEnded(event);
  }
}

//! Forwards event to component to receive key-down events.
void ComponentDrivenApp::keyDown(KeyEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->keyDown(event);
  }
}
//! Forwards event to component to receive key-up events.
void ComponentDrivenApp::keyUp(KeyEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->keyUp(event);
  }
}
//! Forwards event to component to receive window resize events.
void ComponentDrivenApp::resize() {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->resize();
  }
}
//! Forwards event to component to receive file-drop events.
void ComponentDrivenApp::fileDrop(FileDropEvent event) {
  for (auto &comp : getRegisteredGameObjectsCopy()) {
    comp->fileDrop(event);
  }
}

set<GameObjectRef> ComponentDrivenApp::getRegisteredGameObjectsCopy() {
  return set<GameObjectRef>(_registeredGameObjects);
}

ComponentDrivenApp *ComponentDrivenApp::_instance = nullptr;

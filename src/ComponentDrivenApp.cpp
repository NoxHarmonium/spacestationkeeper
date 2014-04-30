//
//  ComponentDrivenApp.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "ComponentDrivenApp.h"
#include "GameComponent.h"

//! Registers a component to receive app events
void ComponentDrivenApp::registerComponent(GameComponent *component) {
  _registeredComponents.push_back(component);
}

//! Get a list of currently registered components
vector<GameComponent *> ComponentDrivenApp::getComponents() {
  return this->_registeredComponents;
}

//! Forwards event to component to perform any application setup after the
// renderer has been initialized.
void ComponentDrivenApp::setup() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->setup();
  }
}
//! Forwards event to component to perform any application cleanup before
// exiting.
void ComponentDrivenApp::shutdown() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->shutdown();
  }
}

//! Forwards event to component to perform any once-per-loop computation.
void ComponentDrivenApp::update() {
  if (!isnan(_lastElapsedTime)) {
    _deltaTime = ci::app::getElapsedSeconds() - _lastElapsedTime;
  }
  _lastElapsedTime = ci::app::getElapsedSeconds();

  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->update();
  }
}
//! Forwards event to component to perform any rendering once-per-loop or in
// response to
// OS-prompted requests for refreshes.
void ComponentDrivenApp::draw() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->draw();
  }
}

//! Forwards event to component to receive mouse-down events.
void ComponentDrivenApp::mouseDown(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseDown(event);
  }
}
//! Forwards event to component to receive mouse-up events.
void ComponentDrivenApp::mouseUp(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseUp(event);
  }
}
//! Forwards event to component to receive mouse-wheel events.
void ComponentDrivenApp::mouseWheel(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseWheel(event);
  }
}
//! Forwards event to component to receive mouse-move events.
void ComponentDrivenApp::mouseMove(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseMove(event);
  }
}
//! Forwards event to component to receive mouse-drag events.
void ComponentDrivenApp::mouseDrag(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseDrag(event);
  }
}

//! Forwards event to component to respond to the beginning of a multitouch
// sequence
void ComponentDrivenApp::touchesBegan(TouchEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->touchesBegan(event);
  }
}
//! Forwards event to component to respond to movement (drags) during a
// multitouch sequence
void ComponentDrivenApp::touchesMoved(TouchEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->touchesMoved(event);
  }
}
//! Forwards event to component to respond to the end of a multitouch sequence
void ComponentDrivenApp::touchesEnded(TouchEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->touchesEnded(event);
  }
}

//! Forwards event to component to receive key-down events.
void ComponentDrivenApp::keyDown(KeyEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->keyDown(event);
  }
}
//! Forwards event to component to receive key-up events.
void ComponentDrivenApp::keyUp(KeyEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->keyUp(event);
  }
}
//! Forwards event to component to receive window resize events.
void ComponentDrivenApp::resize() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->resize();
  }
}
//! Forwards event to component to receive file-drop events.
void ComponentDrivenApp::fileDrop(FileDropEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->fileDrop(event);
  }
}

vector<GameComponent *> ComponentDrivenApp::getRegisteredComponentsCopy() {
  return vector<GameComponent *>(_registeredComponents);
}

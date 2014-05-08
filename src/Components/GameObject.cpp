//
//  GameObject.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#include "GameObject.h"

// Constructors/Destructors
GameObject::GameObject() { renderer = new RenderInfo(); }
GameObject::~GameObject() { delete renderer; }

void GameObject::addComponent(GameComponent *component) {
  _components.insert(component);
}
void GameObject::removeComponent(GameComponent *component) {
  _components.erase(component);
}

//! Forwards event to component to perform any application setup after the
// renderer has been initialized.
void GameObject::setup() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->setup();
  }
}
//! Forwards event to component to perform any application cleanup before
// exiting.
void GameObject::shutdown() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->shutdown();
  }
}

//! Forwards event to component to perform any once-per-loop computation.
void GameObject::update() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->update();
  }
}
//! Forwards event to component to perform any rendering once-per-loop or in
// response to
// OS-prompted requests for refreshes.
void GameObject::draw() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->draw();
  }
}

//! Forwards event to component to receive mouse-down events.
void GameObject::mouseDown(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseDown(event);
  }
}
//! Forwards event to component to receive mouse-up events.
void GameObject::mouseUp(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseUp(event);
  }
}
//! Forwards event to component to receive mouse-wheel events.
void GameObject::mouseWheel(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseWheel(event);
  }
}
//! Forwards event to component to receive mouse-move events.
void GameObject::mouseMove(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseMove(event);
  }
}
//! Forwards event to component to receive mouse-drag events.
void GameObject::mouseDrag(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->mouseDrag(event);
  }
}

//! Forwards event to component to respond to the beginning of a multitouch
// sequence
void GameObject::touchesBegan(TouchEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->touchesBegan(event);
  }
}
//! Forwards event to component to respond to movement (drags) during a
// multitouch sequence
void GameObject::touchesMoved(TouchEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->touchesMoved(event);
  }
}
//! Forwards event to component to respond to the end of a multitouch sequence
void GameObject::touchesEnded(TouchEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->touchesEnded(event);
  }
}

//! Forwards event to component to receive key-down events.
void GameObject::keyDown(KeyEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->keyDown(event);
  }
}
//! Forwards event to component to receive key-up events.
void GameObject::keyUp(KeyEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->keyUp(event);
  }
}
//! Forwards event to component to receive window resize events.
void GameObject::resize() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->resize();
  }
}
//! Forwards event to component to receive file-drop events.
void GameObject::fileDrop(FileDropEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    comp->fileDrop(event);
  }
}

set<GameComponent *> GameObject::getRegisteredComponentsCopy() {
  return set<GameComponent *>(_components);
}

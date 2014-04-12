//
//  ComponentDrivenApp.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "ComponentDrivenApp.h"

//! Registers a component to receive app events
void ComponentDrivenApp::RegisterComponent(GameComponent *component) {
  _registeredComponents.push_back(component);
}

//! Forwards event to component to perform any application setup after the
// renderer has been initialized.
void ComponentDrivenApp::setup() {
  for (auto &comp : _registeredComponents) {
    comp->setup();
  }
}
//! Forwards event to component to perform any application cleanup before
// exiting.
void ComponentDrivenApp::shutdown() {
  for (auto &comp : _registeredComponents) {
    comp->shutdown();
  }
}

//! Forwards event to component to perform any once-per-loop computation.
void ComponentDrivenApp::update() {
  for (auto &comp : _registeredComponents) {
    comp->update();
  }
}
//! Forwards event to component to perform any rendering once-per-loop or in
// response to
// OS-prompted requests for refreshes.
void ComponentDrivenApp::draw() {
  for (auto &comp : _registeredComponents) {
    comp->draw();
  }
}

//! Forwards event to component to receive mouse-down events.
void ComponentDrivenApp::mouseDown(MouseEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->mouseDown(event);
  }
}
//! Forwards event to component to receive mouse-up events.
void ComponentDrivenApp::mouseUp(MouseEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->mouseUp(event);
  }
}
//! Forwards event to component to receive mouse-wheel events.
void ComponentDrivenApp::mouseWheel(MouseEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->mouseWheel(event);
  }
}
//! Forwards event to component to receive mouse-move events.
void ComponentDrivenApp::mouseMove(MouseEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->mouseMove(event);
  }
}
//! Forwards event to component to receive mouse-drag events.
void ComponentDrivenApp::mouseDrag(MouseEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->mouseDrag(event);
  }
}

//! Forwards event to component to respond to the beginning of a multitouch
// sequence
void ComponentDrivenApp::touchesBegan(TouchEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->touchesBegan(event);
  }
}
//! Forwards event to component to respond to movement (drags) during a
// multitouch sequence
void ComponentDrivenApp::touchesMoved(TouchEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->touchesMoved(event);
  }
}
//! Forwards event to component to respond to the end of a multitouch sequence
void ComponentDrivenApp::touchesEnded(TouchEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->touchesEnded(event);
  }
}

//! Forwards event to component to receive key-down events.
void ComponentDrivenApp::keyDown(KeyEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->keyDown(event);
  }
}
//! Forwards event to component to receive key-up events.
void ComponentDrivenApp::keyUp(KeyEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->keyUp(event);
  }
}
//! Forwards event to component to receive window resize events.
void ComponentDrivenApp::resize() {
  for (auto &comp : _registeredComponents) {
    comp->resize();
  }
}
//! Forwards event to component to receive file-drop events.
void ComponentDrivenApp::fileDrop(FileDropEvent event) {
  for (auto &comp : _registeredComponents) {
    comp->fileDrop(event);
  }
}

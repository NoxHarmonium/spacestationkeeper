//
//  GameObject.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#include "GameObject.h"

// Constructors/Destructors
GameObject::GameObject() {
  renderer = new RenderInfo();
  _bindingManager = BindingManager::Instance();
}
GameObject::~GameObject() { delete renderer; }

void GameObject::addComponent(GameComponent *component) {
  _components.insert(component);
  component->gameObject = this; // TODO: Encapsulate more?
}

void GameObject::removeComponent(GameComponent *component) {
  _components.erase(component);
}

RenderInfo *GameObject::getRenderer() { return renderer; }

//! Forwards event to component to perform any application setup after the
// renderer has been initialized.
void GameObject::setup() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    if (comp->enabled &&
        _bindingManager->catchLuaExceptions([comp]() { comp->setup(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to perform any application cleanup before
// exiting.
void GameObject::shutdown() {
  for (auto &comp : getRegisteredComponentsCopy()) {
    if (comp->enabled &&
        _bindingManager->catchLuaExceptions([comp]() { comp->shutdown(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}

//! Forwards event to component to perform any once-per-loop computation.
void GameObject::update() {
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
    if (comp->enabled &&
        _bindingManager->catchLuaExceptions([comp]() { comp->draw(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}

//! Forwards event to component to receive mouse-down events.
void GameObject::mouseDown(MouseEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
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
  for (auto &comp : getRegisteredComponentsCopy()) {
    if (comp->enabled &&
        _bindingManager->catchLuaExceptions([comp]() { comp->resize(); })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}
//! Forwards event to component to receive file-drop events.
void GameObject::fileDrop(FileDropEvent event) {
  for (auto &comp : getRegisteredComponentsCopy()) {
    if (comp->enabled && _bindingManager->catchLuaExceptions([comp, event]() {
                           comp->fileDrop(event);
                         })) {
      cout << "Disabling component..." << endl;
      comp->enabled = false;
    };
  }
}

set<GameComponent *> GameObject::getRegisteredComponentsCopy() {
  return set<GameComponent *>(_components);
}

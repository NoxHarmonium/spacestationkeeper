//
//  GameComponentWrapper.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#ifndef SpaceStationKeeper_GameComponentWrapper_h
#define SpaceStationKeeper_GameComponentWrapper_h

#include "GameComponent.h"
#include "LuaBindDeps.h"

struct GameComponentWrapper : public GameComponent, public luabind::wrap_base {
  GameComponentWrapper() : GameComponent() {}
  // Call registers
  virtual void setup() {
    call<void>("setup");
  };
  virtual void shutdown() {
    call<void>("shutdown");
  };
  virtual void update() {
    call<void>("update");
  };
  virtual void draw() {
    call<void>("draw");
  };
  virtual void mouseDown(MouseEvent event) {
    call<void>("mouseDown", event);
  };
  virtual void mouseWheel(MouseEvent event) {
    call<void>("mouseWheel", event);
  };
  virtual void mouseMove(MouseEvent event) {
    call<void>("mouseMove", event);
  };
  virtual void mouseDrag(MouseEvent event) {
    call<void>("mouseDrag", event);
  };
  virtual void touchesBegan(TouchEvent event) {
    call<void>("touchesBegan", event);
  };
  virtual void touchesMoved(TouchEvent event) {
    call<void>("touchesMoved", event);
  };
  virtual void touchesEnded(TouchEvent event) {
    call<void>("touchesEnded", event);
  };
  virtual void keyDown(KeyEvent event) {
    call<void>("keyDown", event);
  };
  virtual void keyUp(KeyEvent event) {
    call<void>("keyUp", event);
  };
  virtual void resize() {
    call<void>("resize");
  };
  virtual void fileDrop(FileDropEvent event) {
    call<void>("fileDrop", event);
  };

  // Call pointers
  static void default_setup(GameComponent *ptr) {
    return ptr->GameComponent::setup();
  }
  static void default_shutdown(GameComponent *ptr) {
    return ptr->GameComponent::shutdown();
  }
  static void default_update(GameComponent *ptr) {
    return ptr->GameComponent::update();
  }
  static void default_draw(GameComponent *ptr) {
    return ptr->GameComponent::draw();
  }
  static void default_mouseDown(GameComponent *ptr, MouseEvent event) {
    return ptr->GameComponent::mouseDown(event);
  }
  static void default_mouseWheel(GameComponent *ptr, MouseEvent event) {
    return ptr->GameComponent::mouseWheel(event);
  }
  static void default_mouseMove(GameComponent *ptr, MouseEvent event) {
    return ptr->GameComponent::mouseMove(event);
  }
  static void default_mouseDrag(GameComponent *ptr, MouseEvent event) {
    return ptr->GameComponent::mouseDrag(event);
  }
  static void default_touchesBegan(GameComponent *ptr, TouchEvent event) {
    return ptr->GameComponent::touchesBegan(event);
  }
  static void default_touchesMoved(GameComponent *ptr, TouchEvent event) {
    return ptr->GameComponent::touchesMoved(event);
  }
  static void default_touchesEnded(GameComponent *ptr, TouchEvent event) {
    return ptr->GameComponent::touchesEnded(event);
  }
  static void default_keyDown(GameComponent *ptr, KeyEvent event) {
    return ptr->GameComponent::keyDown(event);
  }
  static void default_keyUp(GameComponent *ptr, KeyEvent event) {
    return ptr->GameComponent::keyUp(event);
  }
  static void default_resize(GameComponent *ptr) {
    return ptr->GameComponent::resize();
  }
  static void default_fileDrop(GameComponent *ptr, FileDropEvent event) {
    return ptr->GameComponent::fileDrop(event);
  }
};

#endif

//
//  GameCameraWrapper.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 9/05/2014.
//
//

#ifndef SpaceStationKeeper_GameCameraWrapper_h
#define SpaceStationKeeper_GameCameraWrapper_h

// TODO : DELETE?

#include "LuaBindDeps.h"
#include "GameCamera.h"

struct GameCameraWrapper : public GameCamera, public luabind::wrap_base {
  GameCameraWrapper() : GameCamera() {}
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
  static GameObject *default_gameObject(GameCamera *ptr) {
    return ptr->GameCamera::gameObject;
  }
  static void default_setup(GameCamera *ptr) {
    return ptr->GameCamera::setup();
  }
  static void default_shutdown(GameCamera *ptr) {
    return ptr->GameCamera::shutdown();
  }
  static void default_update(GameCamera *ptr) {
    return ptr->GameCamera::update();
  }
  static void default_draw(GameCamera *ptr) { return ptr->GameCamera::draw(); }
  static void default_mouseDown(GameCamera *ptr, MouseEvent event) {
    return ptr->GameCamera::mouseDown(event);
  }
  static void default_mouseWheel(GameCamera *ptr, MouseEvent event) {
    return ptr->GameCamera::mouseWheel(event);
  }
  static void default_mouseMove(GameCamera *ptr, MouseEvent event) {
    return ptr->GameCamera::mouseMove(event);
  }
  static void default_mouseDrag(GameCamera *ptr, MouseEvent event) {
    return ptr->GameCamera::mouseDrag(event);
  }
  static void default_touchesBegan(GameCamera *ptr, TouchEvent event) {
    return ptr->GameCamera::touchesBegan(event);
  }
  static void default_touchesMoved(GameCamera *ptr, TouchEvent event) {
    return ptr->GameCamera::touchesMoved(event);
  }
  static void default_touchesEnded(GameCamera *ptr, TouchEvent event) {
    return ptr->GameCamera::touchesEnded(event);
  }
  static void default_keyDown(GameCamera *ptr, KeyEvent event) {
    return ptr->GameCamera::keyDown(event);
  }
  static void default_keyUp(GameCamera *ptr, KeyEvent event) {
    return ptr->GameCamera::keyUp(event);
  }
  static void default_resize(GameCamera *ptr) {
    return ptr->GameCamera::resize();
  }
  static void default_fileDrop(GameCamera *ptr, FileDropEvent event) {
    return ptr->GameCamera::fileDrop(event);
  }
};

#endif

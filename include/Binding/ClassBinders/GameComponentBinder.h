//
//  GameComponentBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_GameComponentBinder_h
#define SpaceStationKeeper_GameComponentBinder_h

#include "ClassBinder.h"
#include "GameComponent.h"
#include "GameComponentWrapper.h"

template <> struct ClassBinder<GameComponent> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    module(L)[class_<GameComponent, GameComponentWrapper>(name)
                  .def(constructor<>())
                  .def("setup", &GameComponent::setup,
                       &GameComponentWrapper::default_setup)
                  .def("shutdown", &GameComponent::shutdown,
                       &GameComponentWrapper::default_shutdown)
                  .def("update", &GameComponent::update,
                       &GameComponentWrapper::default_update)
                  .def("draw", &GameComponent::draw,
                       &GameComponentWrapper::default_draw)
                  .def("mouseDown", &GameComponent::mouseDown,
                       &GameComponentWrapper::default_mouseDown)
                  .def("mouseWheel", &GameComponent::mouseWheel,
                       &GameComponentWrapper::default_mouseWheel)
                  .def("mouseMove", &GameComponent::mouseMove,
                       &GameComponentWrapper::default_mouseMove)
                  .def("mouseDrag", &GameComponent::mouseDrag,
                       &GameComponentWrapper::default_mouseDrag)
                  .def("touchesBegan", &GameComponent::touchesBegan,
                       &GameComponentWrapper::default_touchesBegan)
                  .def("touchesMoved", &GameComponent::touchesMoved,
                       &GameComponentWrapper::default_touchesMoved)
                  .def("touchesEnded", &GameComponent::touchesEnded,
                       &GameComponentWrapper::default_touchesEnded)
                  .def("keyDown", &GameComponent::keyDown,
                       &GameComponentWrapper::default_keyDown)
                  .def("keyUp", &GameComponent::keyUp,
                       &GameComponentWrapper::default_keyUp)
                  .def("resize", &GameComponent::resize,
                       &GameComponentWrapper::default_resize)
                  .def("fileDrop", &GameComponent::fileDrop,
                       &GameComponentWrapper::default_fileDrop)];
  }
};

#endif

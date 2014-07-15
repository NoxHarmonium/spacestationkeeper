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
#include <luabind/iterator_ptr_policy.hpp>

namespace BlazeEngine {
namespace Binding {
namespace ClassBinders {

using namespace BlazeEngine::Binding::Wrappers;

template <> struct ClassBinder<SerialisedField> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<SerialisedField, SerialisedFieldRef>(name)
               .def(luabind::constructor<>())
               .def(luabind::constructor<string, string, bool>())
               .def_readonly("name", &SerialisedField::name)
               .def_readonly("type", &SerialisedField::type)
               .def_readonly("getterName", &SerialisedField::getterName)
               .def_readonly("setterName", &SerialisedField::setterName)
               .def_readonly("required", &SerialisedField::required)
               .def_readonly("useAccessors", &SerialisedField::useAccessors)];
  }
};

template <> struct ClassBinder<GameComponent> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)
        [luabind::class_<GameComponent, GameComponentWrapper, GameComponentRef>(
             name)
             .def(luabind::constructor<>())
             .def_readonly("gameObject", &GameComponent::gameObject)
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
             .def("mouseUp", &GameComponent::mouseUp,
                  &GameComponentWrapper::default_mouseUp)
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
                  &GameComponentWrapper::default_fileDrop)
             .def("getSerialisedFields", &GameComponent::getSerialisedFields,
                  luabind::return_stl_iterator)
             .def("serialiseField", (void (GameComponent::*)(string, string)) &
                                        GameComponent::serialiseField)
             .def("serialiseField",
                  (void (GameComponent::*)(string, string, bool)) &
                      GameComponent::serialiseField)
             .def("serialiseField",
                  (void (GameComponent::*)(string, string, string, string)) &
                      GameComponent::serialiseField)
             .def("serialiseField",
                  (void (GameComponent::*)(string, string, string, string,
                                           bool)) &
                      GameComponent::serialiseField)
             .scope[
               luabind::def("getId", &GameComponent::getId),
               luabind::def("setId", &GameComponent::setId)
             ]];
  }
};
}
}
}
/*
template <> struct ClassBinder<vector<GameComponentRef>> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<vector<GameComponentRef>,
                           std::shared_ptr<vector<GameComponentRef>>>(name)
               .def(luabind::constructor<>())
               .def(luabind::constructor<int>())];
  }
};*/

#endif

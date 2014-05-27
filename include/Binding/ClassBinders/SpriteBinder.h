//
//  SpriteBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/05/2014.
//
//

#ifndef SpaceStationKeeper_SpriteBinder_h
#define SpaceStationKeeper_SpriteBinder_h

#include "ClassBinder.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

template <> struct ClassBinder<Sprite> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<Sprite, GameComponent, SpriteRef>(name)
                           .def(luabind::constructor<>())
                           .def(luabind::constructor<TextureDefRef, int>())
                           .def("refresh", &Sprite::refresh)
                           .def("getSpriteTexture", &Sprite::getSpriteTexture)
                           .def("getSpriteFrame", &Sprite::getSpriteFrame)
                           .def("setSpriteTexture", &Sprite::setSpriteTexture)
                           .def("setSpriteFrame", &Sprite::setSpriteFrame)];
  }
};

template <> struct ClassBinder<AnimatedSprite> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<AnimatedSprite, Sprite, AnimatedSpriteRef>(name)
               .def(luabind::constructor<>())
               .def(luabind::constructor<AnimationSetDefRef>())
               .def(luabind::constructor<AnimationSetDefRef, string>())
               .def("getAnimationSet", &AnimatedSprite::getAnimationSet)
               .def("setAnimationSet", &AnimatedSprite::setAnimationSet)
               .def("getAnimationName", &AnimatedSprite::getAnimationName)
               .def("setAnimationName", &AnimatedSprite::setAnimationName)
               .def("getFrameRate", &AnimatedSprite::getFrameRate)
               .def("setFrameRate", &AnimatedSprite::setFrameRate)
               .def("getLoop", &AnimatedSprite::getLoop)
               .def("setLoop", &AnimatedSprite::setLoop)
               .def("reset", &AnimatedSprite::reset)
               .def("play", &AnimatedSprite::play)
               .def("stop", &AnimatedSprite::stop)];
  }
};

#endif

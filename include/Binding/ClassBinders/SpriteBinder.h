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

/*
 void refresh();

 // Fields
 TextureDefRef spriteTexture;
 int spriteFrame = 0;*/

#endif

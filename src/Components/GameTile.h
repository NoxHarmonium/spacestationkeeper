//
//  GameTile.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#ifndef SpaceStationKeeper_GameTile_h
#define SpaceStationKeeper_GameTile_h

#include "GameComponent.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/TriMesh.h"
#include "TextureDef.h"

using namespace cinder::gl;

class GameTile {
public:
  GameTile(TextureDef textureDef, int tileIndex);
  GameTile(TextureDef textureDef, int tileIndex, Vec3f offset);
  void setup();
  void draw();

private:
  Rectf getFrameRect();

  TriMesh *_currentMesh;
  TextureDef _textureDef;
  int _tileIndex;
  Vec3f _offset;
};

#endif

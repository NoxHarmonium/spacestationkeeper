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
#include "RenderComponent.h"
#include "SimpleMesh.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/TriMesh.h"
#include "cinder/gl/GlslProg.h"
#include "TextureDef.h"

using namespace cinder::gl;

class GameTile : public RenderComponent {
public:
  GameTile(TextureDef *textureDef, int tileIndex, ComponentDrivenApp *parent);
  GameTile(TextureDef *textureDef, int tileIndex, Vec3f offset,
           ComponentDrivenApp *parent);
  void setup();

private:
  Rectf getFrameRect();
  int _tileIndex;
};

#endif

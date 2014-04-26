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
#include "Material.h"
#include "EventManager.h"

using namespace cinder::gl;

class GameTile : public RenderComponent {
public:
  GameTile(MaterialRef material, int tileIndex, ComponentDrivenApp *parent);
  GameTile(MaterialRef material, int tileIndex, Vec3f offset,
           ComponentDrivenApp *parent);
  void setup();
  void update();
  void setEventManager(EventManager *eventManager) {
    _eventManager = eventManager;
  }

private:
  Rectf getFrameRect();
  int _tileIndex;
  EventManager *_eventManager = nullptr;
};

#endif

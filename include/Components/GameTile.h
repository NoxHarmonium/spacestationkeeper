//
//  GameTile.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#ifndef SpaceStationKeeper_GameTile_h
#define SpaceStationKeeper_GameTile_h

#include "TriggeredRenderComponent.h"

using namespace cinder::gl;

class GameTile : public TriggeredRenderComponent {
public:
  GameTile(MaterialRef material, int tileIndex, ComponentDrivenApp *parent);
  GameTile(MaterialRef material, int tileIndex, Vec3f offset,
           ComponentDrivenApp *parent);
  void setup();

private:
  Rectf getFrameRect();
  int _tileIndex;
};

#endif

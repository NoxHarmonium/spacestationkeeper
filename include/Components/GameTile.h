//
//  GameTile.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#ifndef SpaceStationKeeper_GameTile_h
#define SpaceStationKeeper_GameTile_h

#include "RenderInfo.h"

using namespace ci;

class GameTile : public RenderInfo {
public:
  GameTile(MaterialRef material, MapPoint mapPoint, int tileIndex);
  GameTile(MaterialRef material, MapPoint mapPoint, int tileIndex, Vec3f offset);
  void setup();
  MapPoint getMapPoint();
  void setTileIndex(int tileIndex);

private:
  Rectf getFrameRect();
  int _tileIndex;
  MapPoint _mapPoint;
};

#endif

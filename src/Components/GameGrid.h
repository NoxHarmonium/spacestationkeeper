//
//  GameGrid.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 13/03/2014.
//
//

#ifndef SpaceStationKeeper_GameGrid_h
#define SpaceStationKeeper_GameGrid_h

#include "GameComponent.h"
#include "GameDef.h"
#include "GameTile.h"
#include "Utils.h"

using namespace std;

class GameGrid : public GameComponent {
public:
  void setup();
  void draw();
  GameGrid(AppNative *parent);

private:
  GameDef _gameDef;
  vector<GameTile *> _tileComponents;
};

#endif

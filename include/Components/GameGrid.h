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
#include "EventManager.h"

using namespace std;

class GameGrid : public RenderComponent {
public:
  void setup();
  void draw();
  void update();
  GameGrid(ComponentDrivenApp *parent);
  GameTile *getTile(int x, int y) { return _gameMap[MapPoint(x, y)]; }

private:
  GameDef _gameDef;
  vector<GameTile *> _tileComponents;
  EventManager *_eventManager;
  map<MapPoint, GameTile *> _gameMap;
};

#endif

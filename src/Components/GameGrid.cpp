//
//  GameGrid.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "GameGrid.h"

using namespace std;

GameGrid::GameGrid(AppNative *parent) : GameComponent(parent) {}

void GameGrid::setup() {
  vector<GameTile *> tiles;
  _gameDef = GameDef::GetTestBoard();
  for (int i = 0; i < _gameDef.width; i++) {
    for (int j = 0; j < _gameDef.height; j++) {
      GameTile *t = new GameTile(_gameDef.tileTexture[i][j],
                                 (int)_gameDef.tileType[i][j]);
      t->setup();
      _tileComponents.push_back(t);
    }
  }
}

void GameGrid::draw() {
  for (auto &tile : _tileComponents) {
    tile->draw();
  }
}

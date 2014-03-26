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
      Vec3f offset = Vec3f(i * _gameDef.tileTexture[i][j].frameWidth,
                           j * _gameDef.tileTexture[i][j].frameHeight, -0.1f);
      GameTile *t = new GameTile(_gameDef.tileTexture[i][j],
                                 (int)_gameDef.tileType[i][j], offset);
      t->setup();
      _tileComponents.push_back(t);
    }
  }
}

void GameGrid::draw() {
  glPushMatrix();
  for (auto &tile : _tileComponents) {
    tile->draw();
  }
  glPopMatrix();
}

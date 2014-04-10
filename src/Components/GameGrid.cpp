//
//  GameGrid.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "GameGrid.h"
#include "FileAssetLoader.h"

using namespace std;

GameGrid::GameGrid(AppNative *parent) : GameComponent(parent) {}

void GameGrid::setup() {

  cout << "GameGrid::setup()" << endl;

  vector<GameTile *> tiles;
  FileAssetLoader *assetLoader = new FileAssetLoader(Utils::getResourcesPath());

  _gameDef = GameDef::GetTestBoard(assetLoader, 20, 20);

  for (int i = 0; i < _gameDef.getWidth(); i++) {
    for (int j = 0; j < _gameDef.getHeight(); j++) {
      GameTile *t = _gameDef.getTile(i, j);
      // cout << "init tile: (" << i << "," << j << "): " << t << endl;
      t->setup();
      _tileComponents.push_back(t);
    }
  }
}

void GameGrid::draw() {

  for (auto &tile : _tileComponents) {
    glPushMatrix();
    tile->draw();
    glPopMatrix();
  }
}

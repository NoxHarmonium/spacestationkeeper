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

  cout << "GameGrid::setup()";

  vector<GameTile *> tiles;
  FileAssetLoader *assetLoader = new FileAssetLoader(Utils::getResourcesPath());

  _gameDef = GameDef::GetTestBoard(assetLoader, 20, 20);

  for (int i = 0; i < _gameDef.getWidth(); i++) {
    for (int j = 0; j < _gameDef.getHeight(); j++) {
      // Vec3f offset =
      //   Vec3f(i * _gameDef.tileTexture[i][j]->getFrameWidth(),
      //         j * _gameDef.tileTexture[i][j]->getFrameHeight(), -0.1f);
      GameTile *t = _gameDef.getTile(i, j);
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

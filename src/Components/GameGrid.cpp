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

GameGrid::GameGrid(ComponentDrivenApp *parent) : GameComponent(parent) {}

void GameGrid::setup() {

  cout << "GameGrid::setup()" << endl;

  vector<GameTile *> tiles;
  FileAssetLoader *assetLoader = new FileAssetLoader(Utils::getResourcesPath());

  _gameDef = GameDef::GetTestBoard(assetLoader, 4, 4);

  TextureDef *asteroidTd =
      (TextureDef *)assetLoader->LoadAsset("tilesets/asteroid");
  // TextureDef *corridorTd =
  //    (TextureDef *)assetLoader->LoadAsset("tilesets/corridor");

  // int frameCount = asteroidTd->getFrameCount();

  for (int i = 0; i < _gameDef.getWidth(); i++) {
    for (int j = 0; j < _gameDef.getHeight(); j++) {
      int frameIndex = asteroidTd->getFrameFromPassibility(
          _gameDef.getMapSquare(MapPoint(i, j)).getPassability());
      Vec3f offset = Vec3f(i * asteroidTd->getFrameWidth(),
                           j * asteroidTd->getFrameHeight(), 0);
      GameTile *t = new GameTile(asteroidTd, frameIndex, offset);
      _gameMap[MapPoint(i, j)] = t;
      _tileComponents.push_back(t);

      t->setup();

      // cout << "create: (" << i << "," << j << "): " << t << endl;
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

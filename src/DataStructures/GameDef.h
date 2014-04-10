//
//  GameDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#ifndef SpaceStationKeeper_GameDef_h
#define SpaceStationKeeper_GameDef_h

#include "TextureDef.h"
#include "filesystem.hpp"
#include <stdlib.h>
#include <map>
#include <iostream>
#include "MapPoint.h"
#include "GameTile.h"

using namespace std;
using namespace boost;

enum TileType { Sides0 = 0, Sides1 = 1, Sides2 = 2, Sides3 = 3, Sides4 = 4 };

enum TileOrientaion { Left = 0, Up = 1, Right = 2, Down = 4 };

class GameDef {

public:
  int getWidth() { return _width; }
  int getHeight() { return _height; }
  GameTile *getTile(int x, int y) { return _gameMap[MapPoint(x, y)]; }

  static GameDef GetTestBoard(AssetLoaderBase *assetLoader, int width,
                              int height) {
    cout << "GameDef::GetTestBoard";
    TextureDef *td = (TextureDef *)assetLoader->LoadAsset("tilesets/corridor");

    int frameCount = td->getFrameCount();

    // cout << "TD address: " << (uint) & td;

    GameDef def = GameDef();
    def._width = width;
    def._height = height;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        int frameIndex = ((i * height) + j) % frameCount;
        Vec3f offset =
            Vec3f(i * td->getFrameWidth(), j * td->getFrameHeight(), 0);
        GameTile *t = new GameTile(td, frameIndex, offset);
        def._gameMap[MapPoint(i, j)] = t;
        // cout << "create: (" << i << "," << j << "): " << t << endl;
      }
    }

    return def;
  };

private:
  int _width;
  int _height;
  map<MapPoint, GameTile *> _gameMap;
};

#endif

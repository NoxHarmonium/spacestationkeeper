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
#include "GameMapSquare.h"

using namespace std;
using namespace boost;

class GameDef {

public:
  int getWidth() { return _width; }
  int getHeight() { return _height; }
  GameMapSquare getMapSquare(MapPoint mapPoint) { return _gameMap[mapPoint]; }

  static GameDef getTestBoard(AssetLoaderBase *assetLoader, int width,
                              int height) {
    cout << "GameDef::getTestBoard()" << endl;

    // cout << "TD address: " << (uint) & td;

    GameDef def = GameDef();
    def._width = width;
    def._height = height;

    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {

        // Not really passability, it is an external texture so assigns
        // orientation
        int passability = 0;
        if (x == 0) {
          passability |= E_Passibility::West;
        }
        if (y == 0) {
          passability |= E_Passibility::North;
        }
        if (x == (width - 1)) {
          passability |= E_Passibility::East;
        }
        if (y == (height - 1)) {
          passability |= E_Passibility::South;
        }

        def._gameMap[MapPoint(x, y)] =
            GameMapSquare(def._defaultTexId, passability);
      }
    }

    return def;
  };

private:
  int _width;
  int _height;
  map<MapPoint, GameMapSquare> _gameMap;
  int _defaultTexId = 0;
};

#endif

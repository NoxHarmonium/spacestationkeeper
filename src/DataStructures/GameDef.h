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

enum TileType { Sides0 = 0, Sides1 = 1, Sides2 = 2, Sides3 = 3, Sides4 = 4 };

enum TileOrientaion { Left = 0, Up = 1, Right = 2, Down = 4 };

struct GameDef {
  TextureDef **tileTexture;
  TileType **tileType;
  TileOrientaion **tileOrientaion;
  int width;
  int height;

  static GameDef GetTestBoard() {
    TextureDef td = TextureDef::loadFromPath("Resources/texturedef.yaml");

    GameDef def = GameDef();
    def.width = 20;
    def.height = 20;
    def.tileTexture = (TextureDef **)calloc(20 * 20, sizeof(TextureDef));
    def.tileType = (TileType **)calloc(20 * 20, sizeof(TileType));
    def.tileOrientaion =
        (TileOrientaion **)calloc(20 * 20, sizeof(TileOrientaion));
    return def;
  };
};

#endif

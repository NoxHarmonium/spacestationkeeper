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
    TextureDef td = TextureDef::loadFromPath(
        "/Users/seandawson/Development/spacestationkeeper/xcode/build/Debug/"
        "SpaceStationKeeper.app/Contents/Resources/texturedef.yaml");

    // cout << "TD address: " << (uint) & td;

    GameDef def = GameDef();
    def.width = 20;
    def.height = 20;
    def.tileTexture = (TextureDef **)calloc(def.width, sizeof(TextureDef *));
    def.tileType = (TileType **)calloc(def.width, sizeof(TileType *));
    def.tileOrientaion =
        (TileOrientaion **)calloc(def.width, sizeof(TileOrientaion *));

    for (int i = 0; i < def.width; i++) {
      def.tileTexture[i] = (TextureDef *)calloc(def.height, sizeof(TextureDef));
      def.tileType[i] = (TileType *)calloc(def.height, sizeof(TileType));
      def.tileOrientaion[i] =
          (TileOrientaion *)calloc(def.height, sizeof(TileOrientaion));

      for (int j = 0; j < def.height; j++) {
        def.tileTexture[i][j] = td;
        def.tileType[i][j] = TileType::Sides0;
        def.tileOrientaion[i][j] = TileOrientaion::Up;
      }
    }

    return def;
  };
};

#endif

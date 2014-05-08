//
//  GameGrid.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 13/03/2014.
//
//

#ifndef SpaceStationKeeper_GameGrid_h
#define SpaceStationKeeper_GameGrid_h

#include "RenderInfo.h"
#include "GameDef.h"
#include "GameTile.h"
#include "Utils.h"
#include "BatchedMesh.h"
#include "TypedEvent.h"
#include <optional.hpp>
#include <tuple>

using namespace std;

class GameGrid : public RenderInfo {
public:
  // Events
  TypedEvent<Vec2i> MouseOverGridSquareEvent = {EventType::Continuous};
  TypedEvent<Vec2i> MouseClickOnGridSquareEvent;

  // Constructors/Destructors
  GameGrid();

  // Methods
  void setup();
  void draw();
  void update();
  void mouseMove(MouseEvent event);
  void fixTileFrameFromAdjacent(
      MapPoint point); // Make corridors and rooms framed properly.
  void fixMultipleTileFrameFromAdjacent(
      MapPoint point); // Make corridors and rooms framed properly.
  bool isPassable(MapPoint point);

  // Getters/Setters
  GameTile *getTile(int x, int y) { return _gameMap[MapPoint(x, y)]; }
  GameTile *getTile(MapPoint point) { return _gameMap[point]; }
  AssetLoaderBase *getAssetLoader() { return _assetLoader; }

private:
  // Fields
  GameDef _gameDef;
  vector<GameTile *> _tileComponents;
  map<MapPoint, GameTile *> _gameMap;
  AssetLoaderBase *_assetLoader;
  BatchedMeshRef _batchedMeshRef;
  Vec2f _gridSize;
  boost::optional<Vec2i> _lastGridCoord;
};

typedef tuple<int, int, int> ThreeInt;

#endif

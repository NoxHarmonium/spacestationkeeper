//
//  MiningJob.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/04/2014.
//
//

#include "MapPoint.h"
#include "GameGrid.h"
#include "Resource.h"
#include "Job.h"
#include "MiningJob.h"
#include "GameTile.h"

// TODO: Everything

MiningJob::MiningJob(GameGrid *gameGrid, MapPoint targetMapPoint,
                     AssetLoaderBase *assetLoader)
    : _gameGrid(gameGrid), _targetMapPoint(targetMapPoint),
      _assetLoader(assetLoader) {};
MiningJob::~MiningJob() {};

bool MiningJob::preRequisitesAreMet() {
  GameTile *tile = _gameGrid->getTile(_targetMapPoint);
  string tileset = tile->material->texture->getFilename();
  return tile != nullptr && tileset == MiningJob::preReqTileSet;
}
bool MiningJob::postRequistesAreMet() {
  GameTile *tile = _gameGrid->getTile(_targetMapPoint);
  string tileset = tile->material->texture->getFilename();
  return tile != nullptr && tileset == MiningJob::postReqTileSet;
}
bool MiningJob::isDone() { return _workUnitsDone >= MiningJob::maxWorkUnits; }
float MiningJob::getProgress() {
  return _workUnitsDone / (float)MiningJob::maxWorkUnits;
}
void MiningJob::update(float deltaTime) {
  float workPerSecond = MiningJob::workUnitPerWorker * 2;
  float workRate = workPerSecond * deltaTime;
  _workUnitProgress += workPerSecond;

  if (_workUnitProgress >= 0.0f) {
    _workUnitsDone++;
    _workUnitProgress = 0.0f;
  }

  if (isDone()) {
    GameTile *tile = _gameGrid->getTile(_targetMapPoint);
    MaterialRef materialCopy = MaterialRef(new Material{*tile->material});
    TextureDefRef corridorTd =
        _assetLoader->loadAsset<TextureDef>(MiningJob::postReqTileSet);
    materialCopy->texture = corridorTd;
    tile->material = materialCopy;
  }
}
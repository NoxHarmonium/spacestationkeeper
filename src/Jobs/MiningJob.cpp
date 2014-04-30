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

MiningJob::MiningJob(GameGrid *gameGrid, MapPoint targetMapPoint,
                     AssetLoaderBase *assetLoader)
    : _gameGrid(gameGrid), _targetMapPoint(targetMapPoint),
      _assetLoader(assetLoader) {};
MiningJob::~MiningJob() {};

bool MiningJob::preRequisitesAreMet() {
  GameTile *tile = _gameGrid->getTile(_targetMapPoint);
  string assetRef = tile->material->texture->getAssetRef();
  cout << "MiningJob::preRequisitesAreMet(): assetRef: " << assetRef
       << " tile addr: " << tile << endl;
  return tile != nullptr && assetRef == string(MiningJob::preReqTileSet);
}
bool MiningJob::postRequistesAreMet() {
  GameTile *tile = _gameGrid->getTile(_targetMapPoint);
  string assetRef = tile->material->texture->getAssetRef();
  return tile != nullptr && assetRef == string(MiningJob::postReqTileSet);
}
bool MiningJob::isDone() { return _workUnitsDone >= MiningJob::maxWorkUnits; }

float MiningJob::getProgress() {
  return _workUnitsDone / (float)MiningJob::maxWorkUnits;
}
void MiningJob::update(float deltaTime) {
  float workPerSecond = MiningJob::workUnitPerWorker * 2;
  float workRate = workPerSecond * deltaTime;
  _workUnitProgress += workRate;

  if (_workUnitProgress >= 1.0f) {
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
    tile->material->baseColor = ColorAf(0.0f, 0.0f, 1.0f, 1.0f);
  }
}
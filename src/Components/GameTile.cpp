//
//  GameTile.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "MapPoint.h"
#include "GameTile.h"
#include "SimpleMesh.h"

using namespace ci;
using namespace std;
using namespace cinder::gl;

GameTile::GameTile(MaterialRef material, MapPoint mapPoint, int tileIndex)
    : _mapPoint(mapPoint), RenderInfo() {
  _tileIndex = tileIndex;
  this->material = material;
  this->transform->localPosition = Vec3f();
}

GameTile::GameTile(MaterialRef material, MapPoint mapPoint, int tileIndex,
                   Vec3f offset)
    : _mapPoint(mapPoint), RenderInfo() {
  _tileIndex = tileIndex;
  this->material = material;
  this->transform->localPosition = offset;
}

Rectf GameTile::getFrameRect() {
  int tileXCount = (this->material->texture->getWidth() /
                    this->material->texture->getFrameWidth());
  int tileYCount = (this->material->texture->getHeight() /
                    this->material->texture->getFrameHeight());
  int xIndex = _tileIndex % tileXCount;
  int yIndex = _tileIndex / tileYCount;
  float normalisedBorderX = this->material->texture->getBorder() /
                            this->material->texture->getWidth();
  float normalisedBorderY = this->material->texture->getBorder() /
                            this->material->texture->getHeight();
  Rectf r;
  r.x1 = (xIndex / (float)tileXCount) + normalisedBorderX;
  r.x2 = ((xIndex + 1) / (float)tileXCount) - normalisedBorderX;
  r.y1 = (yIndex / (float)tileYCount) + normalisedBorderY;
  r.y2 = ((yIndex + 1) / (float)tileYCount) - normalisedBorderY;
  return r;
}

void GameTile::setup() {
  this->mesh = SimpleMesh::generateQuad(this->material->texture->getFrameSize(),
                                        this->getFrameRect());
}

MapPoint GameTile::getMapPoint() { return _mapPoint; }

void GameTile::setTileIndex(int tileIndex) {
  _tileIndex = tileIndex;
  setup();
}

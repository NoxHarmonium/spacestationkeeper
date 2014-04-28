//
//  GameTile.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "GameTile.h"
#include "SimpleMesh.h"

using namespace ci;
using namespace std;
using namespace cinder::gl;

GameTile::GameTile(MaterialRef material, int tileIndex,
                   ComponentDrivenApp *parent)
    : TriggeredRenderComponent(parent) {
  _tileIndex = tileIndex;
  this->material = material;
  this->transform->localPosition = Vec3f();
}

GameTile::GameTile(MaterialRef material, int tileIndex, Vec3f offset,
                   ComponentDrivenApp *parent)
    : TriggeredRenderComponent(parent) {
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
  Rectf r;
  r.x1 = xIndex / (float)tileXCount;
  r.x2 = (xIndex + 1) / (float)tileXCount;
  r.y1 = yIndex / (float)tileYCount;
  r.y2 = (yIndex + 1) / (float)tileYCount;
  return r;
}

void GameTile::setup() {
  this->mesh = SimpleMesh::GenerateQuad(this->material->texture->getFrameSize(),
                                        this->getFrameRect());
}

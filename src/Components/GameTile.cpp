//
//  GameTile.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "GameTile.h"

using namespace ci;
using namespace std;
using namespace cinder::gl;

GameTile::GameTile(TextureDef *textureDef, int tileIndex,
                   ComponentDrivenApp *parent)
    : RenderComponent(parent) {
  _tileIndex = tileIndex;
  this->texture = textureDef;
  this->transform.localPosition = Vec3f();
}

GameTile::GameTile(TextureDef *textureDef, int tileIndex, Vec3f offset,
                   ComponentDrivenApp *parent)
    : RenderComponent(parent) {
  _tileIndex = tileIndex;
  this->texture = textureDef;
  this->transform.localPosition = offset;
}

Rectf GameTile::getFrameRect() {
  int tileXCount = (this->texture->getWidth() / this->texture->getFrameWidth());
  int tileYCount =
      (this->texture->getHeight() / this->texture->getFrameHeight());
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
  this->mesh = SimpleMesh::GenerateQuad(this->texture->getFrameSize(),
                                        this->getFrameRect());
}
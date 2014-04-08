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

GameTile::GameTile(TextureDef *textureDef, int tileIndex) {
  _textureDef = textureDef;
  _tileIndex = tileIndex;
  _offset = Vec3f();
}

GameTile::GameTile(TextureDef *textureDef, int tileIndex, Vec3f offset) {
  _textureDef = textureDef;
  _tileIndex = tileIndex;
  _offset = offset;
}

Rectf GameTile::getFrameRect() {
  int tileXCount = (_textureDef->getWidth() / _textureDef->getFrameWidth());
  int tileYCount = (_textureDef->getHeight() / _textureDef->getFrameHeight());
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

  Rectf frameRect = getFrameRect();

  TriMesh mesh;
  mesh.clear();

  mesh.appendVertex(Vec3f(0, 0, 0)); // appends the vertex
  mesh.appendColorRgb(Color(1.0f, 1.0f, 1.0f));
  mesh.appendTexCoord(Vec2f(frameRect.x1, frameRect.y1));
  mesh.appendVertex(
      Vec3f(0, _textureDef->getHeight(), 0)); // appends the next vertex
  mesh.appendColorRgb(Color(1.0f, 1.0f, 1.0f));
  mesh.appendTexCoord(Vec2f(frameRect.x1, frameRect.y2));
  mesh.appendVertex(
      Vec3f(_textureDef->getWidth(), _textureDef->getHeight(), 0));
  mesh.appendColorRgb(Color(1.0f, 1.0f, 1.0f));
  mesh.appendTexCoord(Vec2f(frameRect.x2, frameRect.y2));
  mesh.appendVertex(Vec3f(_textureDef->getWidth(), 0, 0));
  mesh.appendColorRgb(Color(1.0f, 1.0f, 1.0f));
  mesh.appendTexCoord(Vec2f(frameRect.x2, frameRect.y1));

  int vert0 = mesh.getNumVertices() - 4;
  int vert1 = mesh.getNumVertices() - 1;
  int vert2 = mesh.getNumVertices() - 2;
  int vert3 = mesh.getNumVertices() - 3;

  mesh.appendTriangle(vert0, vert1, vert3);
  mesh.appendTriangle(vert3, vert1, vert2);

  mesh.recalculateNormals();
  mesh.calcBoundingBox();

  _currentMesh = mesh;
}

void GameTile::draw() {
  gl::pushMatrices();
  gl::Texture tex = _textureDef->useTexture();
  tex.enableAndBind();
  gl::translate(_offset);
  gl::draw(_currentMesh);
  tex.unbind();
  _textureDef->releaseTexture();
  gl::popMatrices();
}
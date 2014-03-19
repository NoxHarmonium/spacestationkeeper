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

GameTile::GameTile(TextureDef textureDef, int tileIndex) {
  _textureDef = textureDef;
  _tileIndex = tileIndex;
}

Rectf GameTile::getFrameRect() {
  int tileXCount = (_textureDef.width / _textureDef.frameWidth);
  int tileYCount = (_textureDef.height / _textureDef.frameHeight);
  int xIndex = tileXCount % _tileIndex;
  int yIndex = tileYCount / _tileIndex;
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

  mesh.appendVertex(Vec3f(0, 0, 0)); // appends the vertex
  mesh.appendTexCoord(Vec2f(frameRect.x1, frameRect.y1));
  mesh.appendVertex(Vec3f(0, _textureDef.height, 0)); // appends the next vertex
  mesh.appendTexCoord(Vec2f(frameRect.x1, frameRect.y2));
  mesh.appendVertex(Vec3f(_textureDef.width, _textureDef.height, 0));
  mesh.appendTexCoord(Vec2f(frameRect.x2, frameRect.y2));
  mesh.appendVertex(Vec3f(_textureDef.width, 0, 0));
  mesh.appendTexCoord(Vec2f(frameRect.x2, frameRect.y1));

  // get the index of the vertex. not necessary with this example, but good
  // practice
  int vIdx0 = mesh.getNumVertices() - 4;
  int vIdx1 = mesh.getNumVertices() - 3;
  int vIdx2 = mesh.getNumVertices() - 2;
  int vIdx3 = mesh.getNumVertices() - 1;

  // now create the triangles from the vertices
  mesh.appendTriangle(vIdx0, vIdx1, vIdx2);
  mesh.appendTriangle(vIdx0, vIdx2, vIdx3);

  mesh.recalculateNormals();

  _currentMesh = &mesh;
}

void GameTile::draw() { gl::draw(*_currentMesh); }
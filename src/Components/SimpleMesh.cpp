//
//  SimpleMesh.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#include "SimpleMesh.h"

using namespace ci;
using namespace std;

SimpleMesh::SimpleMesh(TriMesh mesh) { _currentMesh = mesh; }

void SimpleMesh::render() { ci::gl::draw(_currentMesh); }

SimpleMesh *SimpleMesh::generateQuad(Rectf dimensions,
                                     Rectf uvCoords = Rectf(0.0f, 0.0f, 1.0f,
                                                            1.0f)) {

  // cout << "SimpleMesh::GenerateQuad(); dims: " << dimensions
  //     << " uvCoords: " << uvCoords << endl;

  TriMesh mesh;
  mesh.clear();

  // Vertexes
  mesh.appendVertex(Vec3f(dimensions.x1, dimensions.y1, 0));
  mesh.appendVertex(Vec3f(dimensions.x1, dimensions.y2, 0));
  mesh.appendVertex(Vec3f(dimensions.x2, dimensions.y2, 0));
  mesh.appendVertex(Vec3f(dimensions.x2, dimensions.y1, 0));

  // Vertex Colors
  mesh.appendColorRgb(Color(1.0f, 1.0f, 1.0f));
  mesh.appendColorRgb(Color(1.0f, 1.0f, 1.0f));
  mesh.appendColorRgb(Color(1.0f, 1.0f, 1.0f));
  mesh.appendColorRgb(Color(1.0f, 1.0f, 1.0f));

  // Tex coords
  mesh.appendTexCoord(Vec2f(uvCoords.x1, uvCoords.y1));
  mesh.appendTexCoord(Vec2f(uvCoords.x1, uvCoords.y2));
  mesh.appendTexCoord(Vec2f(uvCoords.x2, uvCoords.y2));
  mesh.appendTexCoord(Vec2f(uvCoords.x2, uvCoords.y1));

  int vert0 = mesh.getNumVertices() - 4;
  int vert1 = mesh.getNumVertices() - 1;
  int vert2 = mesh.getNumVertices() - 2;
  int vert3 = mesh.getNumVertices() - 3;

  mesh.appendTriangle(vert0, vert1, vert3);
  mesh.appendTriangle(vert3, vert1, vert2);

  mesh.recalculateNormals();

  SimpleMesh *meshWrapper = new SimpleMesh(mesh);
  meshWrapper->_bounds = mesh.calcBoundingBox();
  return meshWrapper;
}
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

AxisAlignedBox3f SimpleMesh::getBoundingBox() { return _bounds; }

AxisAlignedBox3f SimpleMesh::getBoundingBox(Matrix44f transformMatrix) {
  return _bounds.transformed(transformMatrix);
}

TriMesh *SimpleMesh::getInternalMesh() { return &_currentMesh; }

TriMesh *SimpleMesh::getInternalMesh(Matrix44f transformMatrix) {
  TriMesh *meshCopy = new TriMesh{_currentMesh};
  vector<Vec3f> verts = meshCopy->getVertices();

  for (Vec3f &vertex : meshCopy->getVertices()) {
    vertex = transformMatrix.transformPoint(vertex);
  }
  return meshCopy;
}

SimpleMeshRef SimpleMesh::generateQuad(Rectf dimensions,
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

  SimpleMeshRef meshWrapper = make_shared<SimpleMesh>(mesh);
  meshWrapper->_bounds = mesh.calcBoundingBox();
  return meshWrapper;
}

//
//  BatchedMesh.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 5/05/2014.
//
//

#include "BatchedMesh.h"

// Constructors/Destructors
BatchedMesh::BatchedMesh() {}

BatchedMesh::~BatchedMesh() {}

// Methods
void BatchedMesh::render() {}

TriMesh *BatchedMesh::getInternalMesh() {}

AxisAlignedBox3f BatchedMesh::getBoundingBox() {}

void BatchedMesh::addMesh(BaseMeshRef mesh) { _meshes.push_back(mesh); }

void BatchedMesh::regenerateVboMesh() {
  TriMesh combinedMesh;
  for (BaseMeshRef &mesh : _meshes) {
  }
}
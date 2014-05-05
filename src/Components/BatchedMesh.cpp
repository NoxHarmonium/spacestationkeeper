//
//  BatchedMesh.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 5/05/2014.
//
//

#include "BatchedMesh.h"
#include "NotImplementedException.h"

using namespace ci;
using namespace std;

// Constructors/Destructors
BatchedMesh::BatchedMesh() {}

BatchedMesh::~BatchedMesh() {}

// Methods
void BatchedMesh::render() {
  for (auto &kvp : _dirty) {
    MaterialRef material = kvp.first;
    bool dirty = kvp.second;

    if (dirty) {
      regenerateVboMesh(material);
      kvp.second = false;
    }
  }

  for (auto &kvp : _vboMeshes) {
    MaterialRef material = kvp.first;
    gl::VboMeshRef vboMesh = kvp.second;

    if (vboMesh != nullptr) {
      material->bind();
      gl::draw(vboMesh);
      material->unbind();
    }
  }
}

TriMesh *BatchedMesh::getInternalMesh() { throw new NotImplementedException(); }

TriMesh *BatchedMesh::getInternalMesh(Matrix44f transformMatrix) {
  throw new NotImplementedException();
}

AxisAlignedBox3f BatchedMesh::getBoundingBox() { return _bounds; }

AxisAlignedBox3f BatchedMesh::getBoundingBox(Matrix44f transformMatrix) {
  return _bounds.transformed(transformMatrix);
}

void BatchedMesh::addMesh(MaterialRef material, BaseMeshRef mesh,
                          TransformRef transform) {
  // cout << "BatchedMesh::addMesh(): Adding mesh to batcher: Material: "
  //     << material << " Mesh: " << mesh << endl;

  _meshes[material].push_back(
      mesh->getInternalMesh(transform->getTransformMatrix()));
  _dirty[material] = true;
}

void BatchedMesh::regenerateVboMesh(MaterialRef material) {
  // cout
  //    << "BatchedMesh::regenerateVboMesh(): Regenerating VboMesh for material:
  // "
  //    << material << endl;

  TriMesh combinedMesh;
  vector<Vec3f> vertices;
  vector<ColorAf> colors;
  vector<Vec2f> texCoords;
  vector<uint32_t> indices;
  uint32_t vertCount = 0;

  for (TriMesh *&mesh : _meshes[material]) {
    TriMesh *internalMesh = mesh;

    vertices = internalMesh->getVertices();
    combinedMesh.appendVertices(vertices.data(), vertices.size());

    colors = internalMesh->getColorsRGBA();
    combinedMesh.appendColorsRgba(colors.data(), colors.size());

    texCoords = internalMesh->getTexCoords();
    combinedMesh.appendTexCoords(texCoords.data(), texCoords.size());

    indices = internalMesh->getIndices();
    std::transform(std::begin(indices), std::end(indices), std::begin(indices),
                   [vertCount](uint32_t x) { return x + vertCount; });
    combinedMesh.appendIndices(indices.data(), indices.size());

    vertCount += vertices.size();
  }

  _bounds = Utils::combineBounds(_bounds, combinedMesh.calcBoundingBox());
  _vboMeshes[material] = gl::VboMesh::create(combinedMesh);
}
//
//  BatchedMesh.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 5/05/2014.
//
//

#include "BatchedMesh.h"
#include "NotImplementedException.h"

namespace BlazeEngine {
namespace Components {

using namespace ci;
using namespace std;
using namespace BlazeEngine::Exceptions;

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

TriMesh *BatchedMesh::getInternalMesh() { throw NotImplementedException(); }

TriMesh *BatchedMesh::getInternalMesh(Matrix44f transformMatrix) {
  throw NotImplementedException();
}

AxisAlignedBox3f BatchedMesh::getBoundingBox() { return _bounds; }

AxisAlignedBox3f BatchedMesh::getBoundingBox(Matrix44f transformMatrix) {
  return _bounds.transformed(transformMatrix);
}

void BatchedMesh::addMesh(BatchInfoRef batchInfo) {
  // cout << "BatchedMesh::addMesh(): Adding mesh to batcher: Material: "
  //     << material << " Mesh: " << mesh << endl;
  MaterialRef mat = batchInfo->material;
  _batchMaterials[batchInfo] = mat;
  _meshes[mat].insert(batchInfo);
  _dirty[mat] = true;
}

void BatchedMesh::invalidate(BatchInfoRef batchInfo) {
  // cout << "BatchedMesh::invalidate(): Invalidating mesh..." << endl;
  MaterialRef oldMaterial = _batchMaterials[batchInfo];
  MaterialRef newMaterial = batchInfo->material;

  if (oldMaterial != batchInfo->material) {
    // cout
    //    << "BatchedMesh::invalidate(): BatchInfo has new material.
    // Switching..."
    //    << endl;

    _dirty[oldMaterial] = true;            // Invalidate old material
    _meshes[oldMaterial].erase(batchInfo); // Switch info to new material layer
    _meshes[newMaterial].insert(batchInfo);
    _batchMaterials[batchInfo] = batchInfo->material; // Set new material
  }

  _dirty[batchInfo->material] = true;
}

void BatchedMesh::removeMesh(BatchInfoRef batchInfo) {
  MaterialRef mat = _batchMaterials[batchInfo];
  _batchMaterials.erase(batchInfo);
  _meshes.erase(mat);
  _dirty[mat] = true;
}

void BatchedMesh::regenerateVboMesh(MaterialRef material) {
  // cout << "BatchedMesh::regenerateVboMesh(): Regenerating VboMesh for
  // material:"
  //     << material << endl;

  TriMesh combinedMesh;
  vector<Vec3f> vertices;
  vector<ColorAf> colors;
  vector<Vec2f> texCoords;
  vector<uint32_t> indices;
  uint32_t vertCount = 0;
  _materialBounds[material] = AxisAlignedBox3f();

  for (BatchInfoRef batchInfo : _meshes[material]) {
    TriMesh *internalMesh = batchInfo->mesh->getInternalMesh(
        batchInfo->transform->getTransformMatrixLocal());

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

    _materialBounds[material].include(internalMesh->calcBoundingBox());
  }

  _vboMeshes[material] = gl::VboMesh::create(combinedMesh);

  // Recalculate master bounds
  _bounds = AxisAlignedBox3f();
  for (auto &kvp : _materialBounds) {
    _bounds.include(kvp.second);
  }
}
}
}
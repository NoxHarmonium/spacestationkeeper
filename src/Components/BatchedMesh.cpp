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
  MaterialRef mat = getBatchMaterial(batchInfo->material);
  BaseMeshRef mesh = batchInfo->mesh;
  _batchMaterials[batchInfo] = mat;
  _batchMeshes[batchInfo] = mesh;
  _meshes[mat].insert(batchInfo);

  _dirty[mat] = true;
}

void BatchedMesh::invalidate(BatchInfoRef batchInfo) {
  cout << "BatchedMesh::invalidate(): Invalidating mesh..." << endl;
  MaterialRef oldMaterial = _batchMaterials[batchInfo];
  MaterialRef newMaterial = getBatchMaterial(batchInfo->material);
  BaseMeshRef oldMesh = _batchMeshes[batchInfo];
  BaseMeshRef newMesh = batchInfo->mesh;

  if (oldMaterial != batchInfo->material || oldMesh != newMesh) {
    cout << "BatchedMesh::invalidate(): BatchInfo has new material or mesh. "
            "Switching..." << endl;

    _dirty[oldMaterial] = true;            // Invalidate old material
    _meshes[oldMaterial].erase(batchInfo); // Switch info to new material layer
    _meshes[newMaterial].insert(batchInfo);
    _batchMaterials[batchInfo] = newMaterial; // Set new material
    _batchMeshes[batchInfo] = newMesh;
  }

  _dirty[newMaterial] = true;
}

void BatchedMesh::regenerateVboMesh(MaterialRef material) {
  cout << "BatchedMesh::regenerateVboMesh(): Regenerating VboMesh for material:"
       << material << endl;

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

MaterialRef BatchedMesh::getBatchMaterial(MaterialRef material) {
  if (_meshes.count(material) > 0) {
    return material; // This material is currently the reference material
  }
  for (auto &kvp : _meshes) {
    if (*kvp.first == *material) {
      return kvp.first; // Found material with same properties
    }
  }
  return material;
}
//
//  RenderInfo.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/04/2014.
//
//

#include "RenderInfo.h"
#include <stdexcept>

RenderInfo::RenderInfo() : GameComponent() {
  transform = make_shared<Transform>();
}
RenderInfo::~RenderInfo() {}

// Methods
AxisAlignedBox3f RenderInfo::getBounds() {
  if (mesh) {
    if (!_boundsDirty) {
      return _cachedBounds;
    }
    _cachedBounds =
        mesh->getBoundingBox(this->transform->getTransformMatrixWorld());
    _boundsDirty = false;
    return _cachedBounds;
  }
  return AxisAlignedBox3f();
}

void RenderInfo::draw() {
  if (renderEnabled) {
    startDraw(this);

    if (_batchMode) {
      if (_batchInfoRef == nullptr && this->mesh != nullptr &&
          this->material != nullptr) {
        _batchInfoRef = make_shared<BatchInfo>();
        updateBatchInfo();

        _batchedMeshRef->addMesh(_batchInfoRef); // material without modifiers
      }
      // Rendering of batched mesh should be done elsewhere (where the batched
      // mesh is defined).
    } else {
      if (this->material != nullptr) {
        this->material->bind();
      }
      if (this->mesh != nullptr) {
        this->mesh->render();
      }
      if (this->material != nullptr) {
        this->material->unbind();
      }
    }

    endDraw(this);
  }
}

void RenderInfo::batch(BatchedMeshRef batchedMeshRef) {
  _batchMode = true;
  _batchedMeshRef = batchedMeshRef;
}

void RenderInfo::invalidateBatch() {
  if (!getIsBatched()) {
    throw runtime_error("Cannot invalidate a non batched RenderInfo object. "
                        "Call batch() first.");
  }
  updateBatchInfo();
  _batchedMeshRef->invalidate(_batchInfoRef);
}

bool RenderInfo::getIsBatched() {
  return _batchMode && _batchedMeshRef != nullptr && _batchInfoRef != nullptr;
}

void RenderInfo::startDraw(RenderInfo *renderInfo) {
  glPushMatrix();
  applyTransfromRecursive(renderInfo->transform);
}
void RenderInfo::endDraw(RenderInfo *renderInfo) {
  glPopMatrix();
  _boundsDirty = true; // Invalidate bounds cache once per frame.
}

void RenderInfo::applyTransfromRecursive(TransformRef t) {
  if (t->parent) {
    applyTransfromRecursive(t->parent);
  }
  gl::translate(t->localPosition);
  gl::rotate(t->localRotation);
  gl::scale(t->localScale);
}

void RenderInfo::updateBatchInfo() {
  if (!getIsBatched()) {
    throw runtime_error("Cannot update BatchInfo if this object is not "
                        "batched. Call batch() first.");
  }

  _batchInfoRef->material = this->material;
  _batchInfoRef->mesh = this->mesh;
  _batchInfoRef->transform = this->transform;
}

RenderInfo *RenderInfo::clone() {
  RenderInfo *rClone = new RenderInfo{*this};
  // Make sure that contents is cloned, not just the reference
  rClone->transform = TransformRef(new Transform{*this->transform});
  rClone->material = MaterialRef(new Material{*this->material});

  return rClone;
}

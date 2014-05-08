//
//  RenderInfo.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/04/2014.
//
//

#include "RenderInfo.h"

RenderInfo::RenderInfo() : GameComponent() {}
RenderInfo::~RenderInfo() {}

// Methods
AxisAlignedBox3f RenderInfo::getBounds() {
  if (mesh) {
    if (!_boundsDirty) {
      return _cachedBounds;
    }
    _cachedBounds = mesh->getBoundingBox(this->transform->getTransformMatrix());
    _boundsDirty = false;
    return _cachedBounds;
  }
  return AxisAlignedBox3f();
}

void RenderInfo::draw() {
  if (renderEnabled) {
    RenderInfo *renderInfo = this->getRenderInfo();

    startDraw(renderInfo);

    if (_batchMode) {
      if (!_addedToBatch) {
        _batchedMeshRef->addMesh(this->material, this->mesh,
                                 this->transform); // material without modifiers
        _addedToBatch = true;
      }
      // Rendering of batched mesh should be done elsewhere (where the batched
      // mesh is defined).
    } else {
      renderInfo->material->bind();
      if (this->mesh != nullptr) {
        renderInfo->mesh->render();
      }
      renderInfo->material->unbind();
    }

    endDraw(renderInfo);
  }
}
void RenderInfo::batch(BatchedMeshRef batchedMeshRef) {
  _batchMode = true;
  _batchedMeshRef = batchedMeshRef;
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

RenderInfo *RenderInfo::clone() {
  RenderInfo *rClone = new RenderInfo{*this};
  // Make sure that contents is cloned, not just the reference
  rClone->transform = TransformRef(new Transform{*this->transform});
  rClone->material = MaterialRef(new Material{*this->material});
  return rClone;
}

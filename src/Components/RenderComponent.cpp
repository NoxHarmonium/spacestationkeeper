//
//  RenderComponent.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#include "RenderComponent.h"

using namespace ci;

// Constructors/Destructors
RenderComponent::RenderComponent(ComponentDrivenApp *parent)
    : GameComponent(parent) {};

RenderComponent::~RenderComponent() {}

// Methods
AxisAlignedBox3f RenderComponent::getBounds() {
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

void RenderComponent::draw() {
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
void RenderComponent::batch(BatchedMeshRef batchedMeshRef) {
  _batchMode = true;
  _batchedMeshRef = batchedMeshRef;
}

void RenderComponent::startDraw(RenderInfo *renderInfo) {
  glPushMatrix();
  applyTransfromRecursive(renderInfo->transform);
}
void RenderComponent::endDraw(RenderInfo *renderInfo) {
  glPopMatrix();
  _boundsDirty = true; // Invalidate bounds cache once per frame.
}

void RenderComponent::applyTransfromRecursive(TransformRef t) {
  if (t->parent) {
    applyTransfromRecursive(t->parent);
  }
  gl::translate(t->localPosition);
  gl::rotate(t->localRotation);
  gl::scale(t->localScale);
}
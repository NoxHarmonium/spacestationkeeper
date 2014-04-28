//
//  RenderComponent.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#include "RenderComponent.h"

using namespace ci;

void RenderComponent::draw() {
  if (renderEnabled) {
    RenderInfo *renderInfo = this->getRenderInfo();

    startDraw(renderInfo);

    renderInfo->material->bind();

    if (renderInfo->mesh) {
      renderInfo->mesh->render();
    }

    renderInfo->material->unbind();

    endDraw(renderInfo);
  }
}

void RenderComponent::startDraw(RenderInfo *renderInfo) {
  glPushMatrix();
  applyTransfromRecursive(renderInfo->transform);
}
void RenderComponent::endDraw(RenderInfo *renderInfo) { glPopMatrix(); }

void RenderComponent::applyTransfromRecursive(TransformRef t) {
  if (t->parent) {
    applyTransfromRecursive(t->parent);
  }
  gl::translate(t->localPosition);
  gl::rotate(t->localRotation);
  gl::scale(t->localScale);
}
//
//  RenderComponent.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#include "RenderComponent.h"

using namespace ci;

RenderComponent::RenderComponent(ComponentDrivenApp *parent)
    : GameComponent(parent) {};

void RenderComponent::draw() {
  if (renderEnabled) {
    startDraw();

    material->bind();

    if (this->mesh) {
      this->mesh->Render();
    }

    material->unbind();

    endDraw();
  }
}

void RenderComponent::update() {
  // processEvents();
}

// void RenderComponent::processEvents() {
// if (_eventManager != nullptr) {
//  _eventManager->ProcessTriggers(this);
//}
//}

void RenderComponent::startDraw() {
  glPushMatrix();
  applyTransfromRecursive(&transform);
}
void RenderComponent::endDraw() { glPopMatrix(); }

void RenderComponent::applyTransfromRecursive(Transform *t) {
  if (t->parent) {
    applyTransfromRecursive(t->parent);
  }
  gl::translate(t->localPosition);
  gl::rotate(t->localRotation);
  gl::scale(t->localScale);
}
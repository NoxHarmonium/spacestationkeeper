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

    Material mCopy{*this->material};
    _materialModifier->applyToMaterial(&mCopy);

    mCopy.bind();

    if (this->mesh) {
      this->mesh->Render();
    }

    mCopy.unbind();

    endDraw();
  }
}

void RenderComponent::update() { processEvents(); }

void RenderComponent::processEvents() {
  if (_eventManager != nullptr) {
    this->resetModifiers();
    _eventManager->ProcessTriggers((GameComponent *)this,
                                   this->getTransformModifier(),
                                   this->getMaterialModifier());
  }
}

void RenderComponent::resetModifiers() {
  _transformModifier = TransformModifier::fromTransform(this->transform);
  _materialModifier = MaterialModifier::fromMaterialRef(this->material);
}

void RenderComponent::startDraw() {
  glPushMatrix();
  Transform tCopy = this->transform;
  _transformModifier->applyModification(&tCopy);
  applyTransfromRecursive(&tCopy);
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
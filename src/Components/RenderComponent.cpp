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
    gl::Texture *t = nullptr; // TODO: Use TextureRef (shared_ptr)
    gl::GlslProgRef p = nullptr;

    if (this->texture && (t = this->texture->useTexture())) {
      t->enableAndBind();
      if (this->shader && (p = this->shader->useShader())) {
        p->bind();
        p->uniform("diffuseMap", 0);
        // t->bind(0);
      } else {
        // t->enableAndBind();
      }
    }

    if (this->mesh) {
      this->mesh->Render();
    }

    if (p) {
      p->unbind();
      this->shader->releaseShader();
    }

    if (t) {
      t->unbind();
      this->texture->releaseTexture();
    }

    endDraw();
  }
}
void RenderComponent::startDraw() {
  glPushMatrix();
  applyTransfromRecursive(&this->transform);
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
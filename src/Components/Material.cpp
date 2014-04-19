//
//  Material.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 17/04/2014.
//
//

#include "Material.h"

Material::Material() {
  brightness = 1.0f;
  baseColor = ColorAf(1.0f, 1.0f, 1.0f, 1.0f);
}

void Material::bind() {
  if (tRef != nullptr || pRef != nullptr) {
    cout << "Warning: Material::bind() called without being unbound. Use "
            "Material::unbind() after rendering." << endl;
    unbind();
  }

  if (this->texture && (tRef = this->texture->useTexture())) {
    tRef->enableAndBind();
    if (this->shader && (pRef = this->shader->useShader())) {
      pRef->bind();
      pRef->uniform("diffuseMap", 0);
      pRef->uniform("baseColor", baseColor);
      pRef->uniform("brightness", brightness);
      // t->bind(0);
    } else {
      // t->enableAndBind();
    }
  }
}

void Material::unbind() {
  if (pRef) {
    pRef->unbind();
    this->shader->releaseShader();
  }

  if (tRef) {
    tRef->unbind();
    this->texture->releaseTexture();
  }

  tRef = nullptr;
  pRef = nullptr;
}
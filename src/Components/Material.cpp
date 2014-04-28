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
  if (_tRef != nullptr || _pRef != nullptr) {
    cout << "Warning: Material::bind() called without being unbound. Use "
            "Material::unbind() after rendering." << endl;
    unbind();
  }

  if (this->texture && (_tRef = this->texture->useTexture())) {
    _tRef->enableAndBind();
    if (this->shader && (_pRef = this->shader->useShader())) {
      _pRef->bind();
      _pRef->uniform("diffuseMap", 0);
      _pRef->uniform("baseColor", baseColor);
      _pRef->uniform("brightness", brightness);
      // t->bind(0);
    } else {
      // t->enableAndBind();
    }
  }
}

void Material::unbind() {
  if (_pRef) {
    _pRef->unbind();
    this->shader->releaseShader();
  }

  if (_tRef) {
    _tRef->unbind();
    this->texture->releaseTexture();
  }

  _tRef = nullptr;
  _pRef = nullptr;
}
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

  if (this->texture && (_tRef = this->texture->getAsset())) {
    _tRef->enableAndBind();
    if (this->shader && (_pRef = this->shader->getAsset())) {
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
  }

  if (_tRef) {
    _tRef->unbind();
  }

  _tRef = nullptr;
  _pRef = nullptr;
}

bool operator==(const Material &a, const Material &b) {
  // cout << a.shader << " == " << b.shader << endl;
  return &a.texture == &b.texture && &a.shader == &b.shader &&
         a.baseColor == b.baseColor && a.brightness == b.brightness;
}
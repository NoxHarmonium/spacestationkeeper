//
//  MaterialModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/04/2014.
//
//

#include "MaterialModifier.h"

void MaterialModifier::addToBrightness(float amount) { _brightness += amount; }
void MaterialModifier::multiplyBrightness(float multiplier) {
  _brightness *= multiplier;
}
void MaterialModifier::addToBaseColor(ColorAf amount) { _baseColor += amount; }
void MaterialModifier::multiplyBaseColor(ColorAf multiplier) {
  _baseColor *= multiplier;
}
void MaterialModifier::setShader(ShaderDefRef shaderRef) {
  _shader = shaderRef;
}
void MaterialModifier::setTexture(TextureDefRef textureRef) {
  _texture = textureRef;
}

MaterialModifierRef
MaterialModifier::fromMaterialRef(MaterialRef baseMaterial) {
  return MaterialModifierRef(
      new MaterialModifier(baseMaterial->brightness, baseMaterial->baseColor,
                           baseMaterial->shader, baseMaterial->texture));
}
Material *MaterialModifier::applyToMaterial(Material *source) {
  source->brightness = _brightness;
  source->baseColor = _baseColor;
  source->shader = _shader;
  source->texture = _texture;
  return source;
}
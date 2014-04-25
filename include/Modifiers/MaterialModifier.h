//
//  MaterialModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/04/2014.
//
//

#ifndef SpaceStationKeeper_MaterialModifier_h
#define SpaceStationKeeper_MaterialModifier_h

#include "ShaderDef.h"
#include "TextureDef.h"
#include "Material.h"

using namespace ci;

class MaterialModifier {
public:
  void addToBrightness(float amount);
  void multiplyBrightness(float multiplier);
  void addToBaseColor(ColorAf amount);
  void multiplyBaseColor(ColorAf multiplier);
  void setShader(ShaderDefRef shaderRef);
  void setTexture(TextureDefRef textureRef);

  MaterialModifier *CreateFromMaterial(MaterialRef baseMaterial);
  MaterialRef ApplyToMaterial(MaterialRef source);

private:
  MaterialModifier(float brightness, ColorAf baseColor, ShaderDefRef shader,
                   TextureDefRef texture)
      : _brightness(brightness), _baseColor(baseColor), _shader(shader),
        _texture(texture) {};

  float _brightness;
  ColorAf _baseColor;
  ShaderDefRef _shader;
  TextureDefRef _texture;
};

#endif

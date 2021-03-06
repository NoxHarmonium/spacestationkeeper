//
//  Material.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 17/04/2014.
//
//

#ifndef SpaceStationKeeper_Material_h
#define SpaceStationKeeper_Material_h

#include "TextureDef.h"
#include "ShaderDef.h"

#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"

class Material {
public:
  // Methods
  Material();
  void bind();
  void unbind();

  // Fields
  TextureDefRef texture = nullptr;
  ShaderDefRef shader = nullptr;
  float brightness;
  ColorAf baseColor;

private:
  gl::TextureRef _tRef = nullptr;
  gl::GlslProgRef _pRef = nullptr;
};

typedef std::shared_ptr<Material> MaterialRef;

// Override to compare on values so that batcher can batch materials together
// more efficiently
bool operator==(const Material &a, const Material &b);

#endif

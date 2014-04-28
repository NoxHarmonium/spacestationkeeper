//
//  ShaderModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_ShaderModifier_h
#define SpaceStationKeeper_ShaderModifier_h

#include "Modifier.h"
#include "ShaderDef.h"

class ShaderModifier : public Modifier {
public:
  ShaderModifier(ShaderDefRef shaderRef) : _shaderRef(shaderRef) {};
  ~ShaderModifier() {};

  void apply(RenderInfo *renderInfo);

private:
  ShaderDefRef _shaderRef;
};

#endif

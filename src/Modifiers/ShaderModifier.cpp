//
//  ShaderModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#include "ShaderModifier.h"

void ShaderModifier::apply(RenderInfo *renderInfo) {
  renderInfo->material->shader = _shaderRef;
}
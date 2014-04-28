//
//  TextureModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#include "TextureModifier.h"

void TextureModifier::apply(RenderInfo *renderInfo) {
  renderInfo->material->texture = _textureRef;
}
//
//  TextureModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_TextureModifier_h
#define SpaceStationKeeper_TextureModifier_h

#include "Modifier.h"
#include "TextureDef.h"

class TextureModifier : public Modifier {
public:
  TextureModifier(TextureDefRef textureRef) : _textureRef(textureRef) {};
  ~TextureModifier() {};

  void apply(RenderInfo *renderInfo);

private:
  TextureDefRef _textureRef;
};

#endif

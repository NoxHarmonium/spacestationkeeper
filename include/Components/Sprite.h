//
//  Sprite.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/05/2014.
//
//

#ifndef SpaceStationKeeper_Sprite_h
#define SpaceStationKeeper_Sprite_h

#include "GameComponent.h"
#include "TextureDef.h"
#include <string>
#include <memory>
#include "AssetLoaderBase.h"

class Sprite : public GameComponent {
public:
  // Constants
  static const constexpr char *SpriteShader = "shaders/default";

  // Constructors/Destructors
  Sprite();
  Sprite(TextureDefRef texture, int spriteFrame);
  virtual ~Sprite();

  // Getters/Setters
  TextureDefRef getSpriteTexture();
  int getSpriteFrame();
  void setSpriteTexture(TextureDefRef texture);
  void setSpriteFrame(int frame);

  // Methods
  void setup();
  void refresh();

private:
  // Fields
  TextureDefRef _spriteTexture;
  int _spriteFrame = 0;
  AssetLoaderBase *_assetLoader;
};

typedef std::shared_ptr<Sprite> SpriteRef;

#endif

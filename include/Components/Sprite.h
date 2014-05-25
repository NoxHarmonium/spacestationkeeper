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
#include "Material.h"

struct SpriteCacheEntry {
  SpriteCacheEntry(MaterialRef mat) : material(mat), useCount(1) {}

  MaterialRef material;
  int useCount;
};

typedef std::unique_ptr<SpriteCacheEntry> SpriteCacheEntryPtr;

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

  // Static Fields
  static map<TextureDefRef, SpriteCacheEntryPtr> _materialCache;

  // Methods
  MaterialRef getOrCreateCacheEntry();
  void releaseCache();
};

typedef std::shared_ptr<Sprite> SpriteRef;

#endif

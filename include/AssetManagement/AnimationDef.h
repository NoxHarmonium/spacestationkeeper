//
//  AnimationDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 18/05/2014.
//
//

#ifndef SpaceStationKeeper_AnimationDef_h
#define SpaceStationKeeper_AnimationDef_h

#include "TextureDef.h"

typedef map<string, TextureDefRef> AnimationMap;

class AnimationDef : public AssetDefBaseT<AnimationMap> {
public:
  // Constructors/Destructors
  virtual ~AnimationDef();

  // Methods
  /*! Loads the asset pointed to by this AssetRef object into memory so it can
   * be used. */
  virtual void loadAsset();
  /*! Unloads the asset pointed to by this AssetRef object making it unavailable
   * for use. */
  virtual void unloadAsset();

  // Static Methods
  /*! Constructs an instance of TextureDef from a loaded YAML node. This should
   * be called by an AssetLoader and not directly through scripts. */
  static std::shared_ptr<AnimationDef> FromYamlNode(Node node);

private:
  // Constructors/Destructors
  /*! Constructs a new instance of SpriteDef with values provided through the
   * static method FromYamlNode(). */
  AnimationDef(int id, int width, int height, int frameHeight, int frameWidth,
               float border, map<string, TextureDefRef> animationFileMap);
};

/*! A shared pointer reference to a TextureDef object. */
typedef std::shared_ptr<AnimationDef> AnimationDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * classes AssetType. */
template <> struct GetAssetType<AnimationDef> {
  static const AssetType value = AssetType::Texture;
};

#endif

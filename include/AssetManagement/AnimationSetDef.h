//
//  AnimationSetDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 18/05/2014.
//
//

#ifndef SpaceStationKeeper_AnimationDef_h
#define SpaceStationKeeper_AnimationDef_h

#include "TextureDef.h"

typedef map<string, TextureDefRef> AnimationSetMap;

class AnimationSetDef : public AssetDefBaseT<AnimationSetMap> {
public:
  // Constructors/Destructors
  AnimationSetDef(Node node);
  virtual ~AnimationSetDef();

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
  static std::shared_ptr<AnimationSetDef> FromYamlNode(Node node);

private:
  // Fields
  string _defaultAnimation;
};

/*! A shared pointer reference to a TextureDef object. */
typedef std::shared_ptr<AnimationSetDef> AnimationDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * classes AssetType. */
template <> struct GetAssetType<AnimationSetDef> {
  static const AssetType value = AssetType::AnimationSet;
};

#endif

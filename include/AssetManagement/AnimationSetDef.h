//
//  AnimationSetDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 18/05/2014.
//
//

#ifndef SpaceStationKeeper_AnimationSetDef_h
#define SpaceStationKeeper_AnimationSetDef_h

#include <map>
#include "AssetDefBaseT.h"
#include "AnimationDef.h"

// Type defs
typedef map<string, AnimationDefRef> AnimationSetMap;
typedef std::shared_ptr<AnimationSetMap> AnimationSetMapRef;

class AnimationSetDef : public AssetDefBaseT<AnimationSetMap> {
public:
  // Constructors/Destructors
  AnimationSetDef(Node node);
  virtual ~AnimationSetDef();

  // Getters/Setters
  string getDefaultAnimation();
  void setPath(const filesystem::path path) override;

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
  /*! The animation that is active by default. */
  string _defaultAnimation;
};

/*! A shared pointer reference to a TextureDef object. */
typedef std::shared_ptr<AnimationSetDef> AnimationSetDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * classes AssetType. */
template <> struct GetAssetType<AnimationSetDef> {
  static const AssetType value = AssetType::AnimationSet;
};

#endif

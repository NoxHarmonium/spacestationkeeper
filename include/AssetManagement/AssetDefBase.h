//
//  AssetDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#ifndef SpaceStationKeeper_AssetDefBase_h
#define SpaceStationKeeper_AssetDefBase_h

#include "AssetType.h"
#include "AssetLoaderBase.h"
#include "yaml-cpp/yaml.h"
#include "AssetLoadException.h"

#define ASSETDEF_FILE "assetdef.yaml"

using namespace std;
using namespace YAML;
using namespace boost;

class AssetDefBase {
  // Allows the AssetLoaders to modify internal state.
  friend class AssetLoaderBase;

public:
  // Constructors/Destructors
  AssetDefBase(int id);
  virtual ~AssetDefBase();

  // Getters/Setters
  /*! Gets the string identifier for this assetref that was used to get to load
   * it. (i.e. "tilesets/asteroid") */
  string getAssetRef();
  /*! Sets the string identifier for this assetref that was used to get to load
   * it. (i.e. "tilesets/asteroid") */
  void setAssetRef(string assetRef);
  /*! Gets the unique numeric identifier for this asset. */
  int getId();
  /*! Gets the root directory of the asset */
  virtual filesystem::path getPath();
  /*! Sets the root directory of the asset */
  virtual void setPath(const filesystem::path path);
  /*! Gets the asset pointed to by this assetref object without a specified
   * type. If the asset is not
   * loaded, LoadAsset() is called automatically. */
  std::shared_ptr<void> getAsset();
  /*! Gets whether the asset is loaded into memory or not. */
  bool assetLoaded();
  /*! Gets the type definition of this asset definition. */
  virtual AssetType getAssetType();

  // Methods
  /*! Loads the asset pointed to by this AssetRef object into memory so it can
   * be used. */
  virtual void loadAsset() = 0;
  /*! Unloads the asset pointed to by this AssetRef object making it unavailable
   * for use. */
  virtual void unloadAsset() = 0;

protected:
  // Fields
  /*! The unique numeric identifier for this asset. */
  int _id = -1;
  /*! The string identifier for this assetref that was used to get to load
   * it. (i.e. "tilesets/asteroid") */
  string _assetRef;
  /*! Determines whether the asset should be loaded or not. Used to disable
   * asset loading if it fails. */
  bool _shouldLoad = true;

  // Getters/Setters
  /*! Sets the reference to the asset. */
  std::shared_ptr<void> getAssetPointer();
  /*! Sets the reference to the asset. */
  void setAssetPointer(std::shared_ptr<void> pointer);

private:
  /*! The root directory of the asset. */
  filesystem::path _path; // TODO: Directory path, need to rename to be clearer
  /*! Stores the reference to the asset. */
  std::shared_ptr<void> _assetPointer;
};

typedef std::shared_ptr<AssetDefBase> AssetDefBaseRef;

template <typename T> struct GetAssetType {
  static const AssetType value = AssetType::Unknown;
};

#endif

//
//  AssetDefBaseT.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/05/2014.
//
//

#ifndef SpaceStationKeeper_AssetDefBaseT_h
#define SpaceStationKeeper_AssetDefBaseT_h

#include "AssetDefBase.h"

namespace BlazeEngine {
namespace AssetManagement {

//
// Interface
//

/*! Makes an asset type type specific. Should be inherited from to form
 * AssetDefs. */
template <typename T> class AssetDefBaseT : public AssetDefBase {

public:
  // Constructors/Destructors
  AssetDefBaseT(int id);
  ~AssetDefBaseT();

  // Methods
  /*! Gets the asset pointed to by this assetref object. If the asset is not
   * loaded, LoadAsset() is called automatically. */
  virtual std::shared_ptr<T> getAsset() {
    return static_pointer_cast<T>(AssetDefBase::getAsset());
  }
  /*! Gets the type definition of this asset definition. */
  virtual AssetType getAssetType() {
    AssetType t = AssetDefBase::getAssetType();
    return t;
  }

protected:
  /*! Gets the reference to the asset. */
  virtual std::shared_ptr<T> getAssetPointer() {
    return static_pointer_cast<T>(AssetDefBase::getAssetPointer());
  }
  /*! Sets the reference to the asset. */
  virtual void setAssetPointer(std::shared_ptr<T> pointer) {
    AssetDefBase::setAssetPointer(static_pointer_cast<void>(pointer));
  }
};

//
// Implementation
//

template <typename T>
AssetDefBaseT<T>::AssetDefBaseT(int id)
    : AssetDefBase(id) {}

template <typename T> AssetDefBaseT<T>::~AssetDefBaseT() {}
}
}
#endif

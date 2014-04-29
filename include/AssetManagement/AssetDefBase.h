//
//  AssetDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 30/03/2014.
//
//

#ifndef SpaceStationKeeper_AssetDefBase_h
#define SpaceStationKeeper_AssetDefBase_h

#include "AssetLoaderBase.h"

#define ASSETDEF_FILE "assetdef.yaml"

class AssetDefBase {
  friend class AssetLoaderBase;

public:
  int getRefCount() { return _refCount; }

  virtual int getId() { return _id; }
  virtual std::string getAssetType() = 0;

protected:
  int _refCount = 0;
  int _id = -1;
  bool _shouldLoad = true;
};

typedef std::shared_ptr<AssetDefBase> AssetDefBaseRef;

#endif

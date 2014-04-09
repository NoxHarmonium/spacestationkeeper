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
  int getRefCount() {
    return _refCount;
  };

protected:
  int _refCount = 0;
};

#endif
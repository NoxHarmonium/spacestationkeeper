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

using namespace std;

class AssetDefBase {
  friend class AssetLoaderBase;

public:
  int getRefCount() { return _refCount; }
  string getAssetRef() { return _assetRef; }
  void setAssetRef(string assetRef) { _assetRef = assetRef; }

  virtual int getId() { return _id; }
  virtual string getAssetType() = 0;

protected:
  int _refCount = 0;
  int _id = -1;
  string _assetRef; // The identifier used to access the asset (i.e.
                    // "tilesets/corridor")
  bool _shouldLoad = true;
};

typedef std::shared_ptr<AssetDefBase> AssetDefBaseRef;

#endif

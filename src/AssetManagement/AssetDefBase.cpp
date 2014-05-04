//
//  AssetDefBase.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 3/05/2014.
//
//

#include "AssetDefBase.h"

using namespace boost;

// Constructors/Destructors
AssetDefBase::AssetDefBase(int id) { _id = id; }

AssetDefBase::~AssetDefBase() {};

// Getters/Setters

string AssetDefBase::getAssetRef() { return _assetRef; }

void AssetDefBase::setAssetRef(string assetRef) { _assetRef = assetRef; }

int AssetDefBase::getId() { return _id; }

filesystem::path AssetDefBase::getPath() { return _path; }

void AssetDefBase::setPath(const filesystem::path path) { _path = path; }

std::shared_ptr<void> AssetDefBase::getAsset() {
  loadAsset();
  return _assetPointer;
}

void AssetDefBase::setAssetPointer(std::shared_ptr<void> pointer) {
  _assetPointer = pointer;
}

bool AssetDefBase::assetLoaded() { return _assetPointer != nullptr; }

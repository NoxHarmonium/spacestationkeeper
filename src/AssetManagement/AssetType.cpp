//
//  AssetType.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#include "AssetType.h"

namespace BlazeEngine {
namespace AssetManagement {

ostream &operator<<(ostream &os, const AssetType &assetType) {
  switch (assetType) {
  case AssetType::Unknown:
    os << "Unknown";
    break;
  case AssetType::Texture:
    os << "Texture";
    break;
  case AssetType::Shader:
    os << "Shader";
    break;
  case AssetType::Audio:
    os << "Audio";
    break;
  case AssetType::Script:
    os << "Script";
    break;
  case AssetType::AnimationSet:
    os << "AnimationSet";
    break;
  case AssetType::Animation:
    os << "Animation";
    break;
  }

  return os;
}
}
}
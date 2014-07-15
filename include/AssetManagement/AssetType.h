//
//  AssetType.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 31/03/2014.
//
//

#ifndef SpaceStationKeeper_AssetType_h
#define SpaceStationKeeper_AssetType_h

#include <ostream>

using namespace std;

#define ASSET_TEXTURE "Texture"
#define ASSET_SHADER "Shader"
#define ASSET_AUDIO "Audio"
#define ASSET_SCRIPT "Script"
#define ASSET_ANIMATIONSET "AnimationSet"
#define ASSET_ANIMATION "Animation"
#define ASSET_UNKNOWN "Unknown"

namespace BlazeEngine {
namespace AssetManagement {

/*! A enum of all the known asset types. */
enum AssetType {
  Unknown,
  Texture,
  Shader,
  Audio,
  Script,
  AnimationSet,
  Animation
};

ostream &operator<<(ostream &os, const AssetType &assetType);
}
}

#endif

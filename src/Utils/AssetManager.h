//
//  AssetManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#ifndef __SpaceStationKeeper__AssetManager__
#define __SpaceStationKeeper__AssetManager__

//#include "filesystem.hpp"
//#include "filesystem/fstream.hpp"
#include "cinder/gl/Texture.h"
#include "TextureDef.h"

using namespace cinder;

class AssetManager {
public:
  AssetManager();
  gl::Texture getTexture(TextureDef textureDef);
};

#endif /* defined(__SpaceStationKeeper__AssetManager__) */

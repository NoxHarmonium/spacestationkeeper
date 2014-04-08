//
//  Utils.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#ifndef __SpaceStationKeeper__Utils__
#define __SpaceStationKeeper__Utils__

#include <stdlib.h>
#include "boost/filesystem/fstream.hpp"
#include <libproc.h>
#include "filesystem.hpp"

#define OSX_RESOURCE_DIR "../Resources"

using namespace boost;

class Utils {
public:
  static filesystem::path getCurrentExecutablePath();
  static filesystem::path getResourcesPath();
};

#endif /* defined(__SpaceStationKeeper__Utils__) */

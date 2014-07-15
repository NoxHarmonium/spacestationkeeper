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
#include "yaml-cpp/yaml.h"
#include "AssetLoadException.h"

namespace BlazeEngine {
namespace Misc {

using namespace std;
using namespace YAML;
using namespace boost;
using namespace ci;
using namespace BlazeEngine::Exceptions;

class Utils {
public:
  // Static Methods
  static BOOL existsIn(std::string sourceString, std::string searchString);
  static std::string strToUpper(std::string inputString);
  static bool isInside(ci::AxisAlignedBox3f bounds, ci::Vec2f point);
  static bool isInside(ci::AxisAlignedBox3f bounds, ci::Vec3f point);
  static bool areOverlapping(ci::AxisAlignedBox3f bounds, ci::Rectf rect);
  static void printOpenGlVersionInfo();
  static bool getChildNode(Node *childNode, Node node, string key,
                           bool required = true);
  static AxisAlignedBox3f combineBounds(AxisAlignedBox3f first,
                                        AxisAlignedBox3f second);
  // Template Methods
  /*! Parses a value from a YAML node referenced by key and validates it.
   * Should
   * be used when parsing AssetDefs so that the exceptions that are thrown
   * are
   * consistant. */
  template <typename T2>
  static bool parseNode(T2 *targetVar, Node node, string key,
                        bool required = true) {
    Node childNode;
    bool exists = getChildNode(&childNode, node, key, required);
    if (!exists) {
      return false;
    }

    try {
      *targetVar = childNode.as<T2>();
    }
    catch (const YAML::BadConversion &e) {
      // Catch format error
      throw AssetLoadException(
          AssetLoadException::AssetLoadExceptionReason::AssetDefInvalidFormat,
          key);
    }
    catch (const std::exception &e) {
      // Hopefully catch all other exceptions
      throw AssetLoadException(&e);
    }
    return true;
  }
};
}
}

#endif /* defined(__SpaceStationKeeper__Utils__) */

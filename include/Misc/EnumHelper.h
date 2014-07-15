//
//  EnumHelper.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 10/04/2014.
//
//

#ifndef __SpaceStationKeeper__EnumHelper__
#define __SpaceStationKeeper__EnumHelper__

#include <iostream>
#include <stdlib.h>
#include <unordered_set>
#include <type_traits>

namespace BlazeEngine {
namespace Misc {

class EnumHelper {

public:
  EnumHelper();
  EnumHelper(int initialValue) : _internalValue(initialValue) {};
  void setFlag(int value);
  void clearFlag(int value);
  bool hasFlag(int value);
  int getInternalValue();

  operator int() { return _internalValue; }

  friend std::ostream &operator<<(std::ostream &out, EnumHelper &helper);

private:
  int _internalValue = 0;
};
}
}

#endif /* defined(__SpaceStationKeeper__EnumHelper__) */

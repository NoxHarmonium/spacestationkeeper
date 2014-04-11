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

class EnumHelper {

public:
  EnumHelper();
  void setFlag(int value);
  void clearFlag(int value);
  bool hasFlag(int value);

  friend std::ostream &operator<<(std::ostream &out, EnumHelper &helper);

private:
  std::unordered_set<int> _internalValue;
};

#endif /* defined(__SpaceStationKeeper__EnumHelper__) */

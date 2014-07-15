//
//  Passibility.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 9/04/2014.
//
//

#ifndef SpaceStationKeeper_Passibility_h
#define SpaceStationKeeper_Passibility_h

#include "EnumHelper.h"

namespace BlazeEngine {
namespace DataStructures {

using namespace BlazeEngine::Misc;

class Passibility : public EnumHelper {
public:
  Passibility() : EnumHelper() {}
  Passibility(int initialValue) : EnumHelper(initialValue) {}
  enum E_Passibility {
    None = 0,
    North = 1 << 0,
    South = 1 << 1,
    East = 1 << 2,
    West = 1 << 3,
    Unused = 1 << 4
  };
};
}
}

#endif

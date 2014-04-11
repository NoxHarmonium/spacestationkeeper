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

enum E_Passibility {
  None = 1 << 0,
  North = 1 << 1,
  South = 1 << 2,
  East = 1 << 3,
  West = 1 << 4
};

typedef EnumHelper Passibility;

#endif

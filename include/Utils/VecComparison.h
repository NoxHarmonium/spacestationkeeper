//
//  VecComparison.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/05/2014.
//
//

#ifndef SpaceStationKeeper_VecComparison_h
#define SpaceStationKeeper_VecComparison_h

using namespace ci;

struct VecComparison {
  bool operator()(const Vec2i &lhs, const Vec2i &rhs) const {
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
  }
};

#endif

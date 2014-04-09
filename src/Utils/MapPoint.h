//
//  MapPoint.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/04/2014.
//
//

#ifndef SpaceStationKeeper_MapPoint_h
#define SpaceStationKeeper_MapPoint_h

struct MapPoint {
  // Thanks: http://stackoverflow.com/a/4311/1153203
  MapPoint(int x, int y) : x(x), y(y) {}
  int x;
  int y;
  bool operator<(const MapPoint &other) const {
    return std::tie(x, y) < std::tie(other.x, other.y);
  }

  bool operator==(const MapPoint &other) const {
    return (x == other.x && y == other.y);
  }
};

#endif

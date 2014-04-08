//
//  MapPoint.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/04/2014.
//
//

#ifndef SpaceStationKeeper_MapPoint_h
#define SpaceStationKeeper_MapPoint_h

class MapPoint {
  // Thanks: http://stackoverflow.com/a/4311/1153203
public:
  MapPoint(int x, int y) {
    this->x = x;
    this->y = y;
  }
  int x;
  int y;
  bool operator<(const MapPoint &other) const {
    return (x < other.x && y < other.y);
  }
};

#endif

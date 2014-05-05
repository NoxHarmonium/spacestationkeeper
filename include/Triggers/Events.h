//
//  Events.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 22/04/2014.
//
//

#ifndef SpaceStationKeeper_Events_h
#define SpaceStationKeeper_Events_h

#include <stdlib.h>

class Events {
public:
  static constexpr const char *MouseOver = "MouseOver";
  static constexpr const char *MouseClick = "MouseClick";
  static constexpr const char *ComponentSelected = " ComponentSelected";
  static constexpr const char *MouseDragAreaOver = "MouseDragAreaOver";
  static constexpr const char *MouseDragAreaRelease = "MouseDragAreaRelease";
};

#endif

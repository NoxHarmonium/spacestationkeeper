//
//  GameMapSquare.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 11/04/2014.
//
//

#ifndef SpaceStationKeeper_GameMapSquare_h
#define SpaceStationKeeper_GameMapSquare_h

#include "Passibility.h"

class GameMapSquare {
public:
  GameMapSquare() : _tileTexId(0), _passability(0) {}
  GameMapSquare(int tileTexId, int passability)
      : _tileTexId(tileTexId), _passability(passability) {}
  int getTileTexId() { return _tileTexId; }
  Passibility getPassability() { return Passibility(_passability); }

private:
  int _tileTexId;
  int _passability;
};

#endif

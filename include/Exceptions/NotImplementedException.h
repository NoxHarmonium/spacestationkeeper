//
//  NotImplementedException.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/05/2014.
//
//

#ifndef SpaceStationKeeper_NotImplementedException_h
#define SpaceStationKeeper_NotImplementedException_h

#include <stdexcept>

class NotImplementedException : public runtime_error {
public:
  // Constructors/Destructors
  NotImplementedException()
      : runtime_error("This method has not been implemented yet.") {};
  ~NotImplementedException() {};
};

#endif

//
//  SteeringBehaviour.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

#ifndef SpaceStationKeeper_SteeringBehaviour_h
#define SpaceStationKeeper_SteeringBehaviour_h

#include "SteeringTarget.h"

namespace BlazeEngine {
namespace AI {
namespace Steering {

// Based on
// http://andrewfray.wordpress.com/2013/03/26/context-behaviours-know-how-to-share/
class SteeringBehaviour {
public:
  enum class ContextType { Interest, Danger };

  // Constructor/Destructor
  SteeringBehaviour(SteeringTargetRef target, int resoulution);
  virtual ~SteeringBehaviour();

  // Getters/Setters
  SteeringTargetRef getTarget();
  int getResolution();

  // Methods
  void fillContextSlots(float contextSlots[]);

  // Abstract Methods
  virtual float getContextValue(const float angle,
                                const ContextType contextType);

private:
  // Fields
  int _resolution;
  SteeringTargetRef _target;
};
}
}
}
#endif

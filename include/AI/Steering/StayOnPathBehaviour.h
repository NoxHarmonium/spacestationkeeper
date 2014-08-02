//
//  StayOnPathBehaviour.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

#ifndef SpaceStationKeeper_StayOnPathBehaviour_h
#define SpaceStationKeeper_StayOnPathBehaviour_h

#include "SteeringBehaviour.h"
#include "Path.h"

namespace BlazeEngine {
namespace AI {
namespace Steering {

class StayOnPathBehaviour : public SteeringBehaviour {
public:
  // Constructor/Destructor
  StayOnPathBehaviour(SteeringTargetRef steeringTarget, int resoulution,
                      Pathing::PathRef path, float predictionTime = 1.0f);
  virtual ~StayOnPathBehaviour();

  // Virtual Methods
  virtual float getContextValue(const ContextSlotType angle,
                                const ContextType contextType) override;

private:
  float _predictionTime;
  Pathing::PathRef _path;
};
}
}
}
#endif

//
//  SteeringTarget.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

#ifndef SpaceStationKeeper_SteeringTarget_h
#define SpaceStationKeeper_SteeringTarget_h

#include <memory>
#include <list>
#include "Transform.h"
#include "Neighbourhood.h"

namespace BlazeEngine {
namespace AI {
namespace Steering {

using namespace ci;
using namespace BlazeEngine::Components;

class SteeringTarget;
typedef std::shared_ptr<SteeringTarget> SteeringTargetRef;

typedef std::shared_ptr<Neighbourhood<SteeringTarget>> NeighbourhoodRef;

using namespace std;

class SteeringTarget {

public:
  SteeringTarget(NeighbourhoodRef neighbourhood);
  virtual ~SteeringTarget();

  float getMaxSpeed();
  void setMaxSpeed(float maxSpeed);
  float getSpeed();
  NeighbourhoodRef getNeighbourhood();

  Vec3f predictFuturePosition(float secondsInFuture);

private:
  TransformRef _transform;
  Vec3f _velocity;
  float _maxSpeed;
  NeighbourhoodRef _neighbourhood;
};
}
}
}

#endif

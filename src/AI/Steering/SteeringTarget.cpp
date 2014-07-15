//
//  SteeringTarget.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

#include "SteeringTarget.h"

namespace BlazeEngine {
namespace AI {
namespace Steering {

SteeringTarget::SteeringTarget(NeighbourhoodRef neighbourhood)
    : _neighbourhood(neighbourhood) {
  _transform = make_shared<Transform>();
}

SteeringTarget::~SteeringTarget() {}

float SteeringTarget::getMaxSpeed() { return _maxSpeed; }
void SteeringTarget::setMaxSpeed(float maxSpeed) { _maxSpeed = maxSpeed; }

float SteeringTarget::getSpeed() { return _velocity.length(); }

NeighbourhoodRef SteeringTarget::getNeighbourhood() { return _neighbourhood; }

Vec3f SteeringTarget::predictFuturePosition(float secondsInFuture) {
  return _transform->localPosition + (_velocity * secondsInFuture);
}
}
}
}
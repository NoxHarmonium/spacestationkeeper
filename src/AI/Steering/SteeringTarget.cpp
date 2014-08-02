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

SteeringTarget::SteeringTarget() : _renderableRef(nullptr) {}

SteeringTarget::SteeringTarget(RenderableRef renderableRef)
    : _renderableRef(renderableRef) {}

SteeringTarget::~SteeringTarget() {}

Components::TransformRef SteeringTarget::getTransformRef() {
  if (_renderableRef == nullptr) {
    return nullptr;
  }
  return _renderableRef->renderer->transform;
}

float SteeringTarget::getMaxSpeed() { return _maxSpeed; }
void SteeringTarget::setMaxSpeed(float maxSpeed) { _maxSpeed = maxSpeed; }

float SteeringTarget::getSpeed() { return _velocity.length(); }

Vec3f SteeringTarget::predictFuturePosition(float secondsInFuture) {
  if (_renderableRef == nullptr) {
    return Vec3f::zero();
  }

  Components::TransformRef t = _renderableRef->renderer->transform;

  return t->localPosition + (_velocity * secondsInFuture);
}

RenderableRef SteeringTarget::getRenderableRef() { return _renderableRef; }
}
}
}
//
//  StayOnPathBehaviour.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//  Based on logic from the OpenSteer library.
//

#include "StayOnPathBehaviour.h"
#include <math.h>

namespace BlazeEngine {
namespace AI {
namespace Steering {

// Constructor/Destructor
StayOnPathBehaviour::StayOnPathBehaviour(SteeringTargetRef steeringTarget,
                                         int resoulution, Pathing::PathRef path,
                                         float predictionTime)
    : SteeringBehaviour(steeringTarget, resoulution), _path(path),
      _predictionTime(predictionTime) {}

StayOnPathBehaviour::~StayOnPathBehaviour() {}

float StayOnPathBehaviour::getContextValue(const float angle,
                                           const ContextType contextType) {
  SteeringTargetRef target = getTarget();
  // NeighbourhoodRef n = target->getNeighbourhood();
  switch (contextType) {
  case ContextType::Interest: {
    Components::TransformRef t = target->getTransformRef();
    Vec3f dir = Vec3f(sinf(angle) * _predictionTime,
                      cosf(angle) * _predictionTime, 0.0f);
    Vec3f projectedPos = t->localPosition + dir;

    // See how far projected point is down path
    float pathDistance =
        _path->getPathDistanceFromPoint(Vec2f(projectedPos.x, projectedPos.y));

    // Normalise 0.0-1.0
    return pathDistance / _path->getTotalDistance();

    break;
  }
  case ContextType::Danger: {
    // Stay on path doesn't detect danger
    return 0.0f;
    break;
  }
  default:
    throw std::runtime_error("Invalid context type.");
  }
  // float pathDistanceOffset = _predictionTime * target->getSpeed();
  // Vec3f futurePosition = target->predictFuturePosition(_predictionTime);
}

/*

 steerToFollowPath (const int direction,
 const float predictionTime,
 Pathway& path)
 {
 --// our goal will be offset from our path distance by this amount
 --const float pathDistanceOffset = direction * predictionTime * speed();

 // predict our future position
 const Vec3 futurePosition = predictFuturePosition (predictionTime);

 // measure distance along path of our current and predicted positions
 const float nowPathDistance =
 path.mapPointToPathDistance (position ());
 const float futurePathDistance =
 path.mapPointToPathDistance (futurePosition);

 // are we facing in the correction direction?
 const bool rightway = ((pathDistanceOffset > 0) ?
 (nowPathDistance < futurePathDistance) :
 (nowPathDistance > futurePathDistance));

 // find the point on the path nearest the predicted future position
 // XXX need to improve calling sequence, maybe change to return a
 // XXX special path-defined object which includes two Vec3s and a
 // XXX bool (onPath,tangent (ignored), withinPath)
 Vec3 tangent;
 float outside;
 const Vec3 onPath = path.mapPointToPath (futurePosition,
 // output arguments:
 tangent,
 outside);

 // no steering is required if (a) our future position is inside
 // the path tube and (b) we are facing in the correct direction
 if ((outside < 0) && rightway)
 {
 // all is well, return zero steering
 return Vec3::zero;
 }
 else
 {
 // otherwise we need to steer towards a target point obtained
 // by adding pathDistanceOffset to our current path position

 float const targetPathDistance = nowPathDistance + pathDistanceOffset;
 Vec3 const target = path.mapPathDistanceToPoint (targetPathDistance);

 annotatePathFollowing (futurePosition, onPath, target, outside);

 // return steering to seek target on path
 return steerForSeek (target);
 }
 }
*/
}
}
}
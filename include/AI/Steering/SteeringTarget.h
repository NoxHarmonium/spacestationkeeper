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
#include "RenderInfo.h"
#include "Renderable.h"

namespace BlazeEngine {
namespace AI {
namespace Steering {

using namespace ci;
using namespace BlazeEngine::Components;
namespace Components = BlazeEngine::Components;

class SteeringTarget;
typedef std::shared_ptr<SteeringTarget> SteeringTargetRef;

using namespace std;

class SteeringTarget {

public:
  SteeringTarget();
  SteeringTarget(Components::RenderableRef renderableRef);
  virtual ~SteeringTarget();

  Components::TransformRef getTransformRef();
  float getMaxSpeed();
  void setMaxSpeed(float maxSpeed);
  float getSpeed();
  Vec3f predictFuturePosition(float secondsInFuture);

  virtual RenderableRef getRenderableRef();

private:
  Components::RenderableRef _renderableRef;
  Vec3f _velocity;
  float _maxSpeed;
};
}
}
}

#endif

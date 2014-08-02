//
//  SteeringBehaviour.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

#include "SteeringBehaviour.h"
#include <math.h>

namespace BlazeEngine {
namespace AI {
namespace Steering {

// Constructor/Destructor
SteeringBehaviour::SteeringBehaviour(SteeringTargetRef target, int resoulution)
    : _target(target), _resolution(resoulution) {}

SteeringBehaviour::~SteeringBehaviour() {}

// Getters/Setters
SteeringTargetRef SteeringBehaviour::getTarget() { return _target; }

int SteeringBehaviour::getResolution() { return _resolution; }

// Methods
void SteeringBehaviour::fillContextSlots(ContextSlots &contextSlots) {
  float anglePerSlot = 360 / (float)_resolution;
  int contextTypeCount = 2;
  ContextType contextTypes[] = {ContextType::Interest, ContextType::Danger};

  for (int i = 0; i < contextTypeCount; i++) {
    ContextType contextType = contextTypes[i];
    int startIndex = i * _resolution;
    for (int j = startIndex; j < startIndex + getResolution(); j++) {
      contextSlots[j] =
          fmax(contextSlots[j], getContextValue(anglePerSlot * j, contextType));
    }
  }
}
}
}
}
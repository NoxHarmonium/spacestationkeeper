//
//  RotateModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#include "RotateModifier.h"

void RotateModifier::apply(RenderInfo *renderInfo) {
  // Needs to be multipled in this order to apply delta rotation (multiply is
  // not symetrical)
  // TODO: Check this is correct operation
  renderInfo->transform->localRotation =
      _rotation * renderInfo->transform->localRotation;
}
//
//  ScaleModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#include "ScaleModifier.h"

void ScaleModifier::apply(RenderInfo *renderInfo) {
  renderInfo->transform->localScale *= _scale;
}
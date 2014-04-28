//
//  TranslateModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#include "TranslateModifier.h"

void TranslateModifier::apply(RenderInfo *renderInfo) {
  renderInfo->transform->localPosition += _translation;
}
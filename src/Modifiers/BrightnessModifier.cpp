//
//  BrightnessModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#include "BrightnessModifier.h"

void BrightnessModifier::apply(RenderInfo *renderInfo) {
  switch (_mode) {
  case ModifyMode::Add:
    renderInfo->material->brightness += _factor;
    break;

  case ModifyMode::Multiply:
    renderInfo->material->brightness *= _factor;
    break;

  default:
    cout << "Unrecognized ModifyMode" << endl;
    throw std::exception();
    break;
  }
}
//
//  BaseColorModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#include "BaseColorModifier.h"

void BaseColorModifier::apply(RenderInfo *renderInfo) {
  switch (_mode) {
  case ModifyMode::Add:
    renderInfo->material->baseColor += _factor;
    break;

  case ModifyMode::Multiply:
    renderInfo->material->baseColor *= _factor;
    break;

  default:
    cout << "Unrecognized ModifyMode" << endl;
    throw std::exception();
    break;
  }
}
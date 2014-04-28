//
//  RenderInfo.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/04/2014.
//
//

#include "RenderInfo.h"

RenderInfo *RenderInfo::clone() {
  RenderInfo *rClone = new RenderInfo{*this};
  // Make sure that contents is cloned, not just the reference
  rClone->transform = TransformRef(new Transform{*this->transform});
  rClone->material = MaterialRef(new Material{*this->material});
  return rClone;
}
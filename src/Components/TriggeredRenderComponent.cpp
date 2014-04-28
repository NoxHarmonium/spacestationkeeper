//
//  TriggeredRenderComponent.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/04/2014.
//
//

#include "TriggeredRenderComponent.h"

RenderInfo *TriggeredRenderComponent::getRenderInfo() {
  return _modifiedRenderInfo;
}

void TriggeredRenderComponent::update() {
  if (_eventManager != nullptr) {
    _modifiers = _eventManager->processTriggers(this);
  }
  if (_modifiedRenderInfo != nullptr) {
    delete _modifiedRenderInfo;
  }
  _modifiedRenderInfo = this->clone();
  for (auto &mod : _modifiers) {
    mod->apply(_modifiedRenderInfo);
    delete mod;
  }
}
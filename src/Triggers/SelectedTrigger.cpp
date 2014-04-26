//
//  SelectedTrigger.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/04/2014.
//
//

#include "SelectedTrigger.h"

SelectedTrigger::SelectedTrigger(ComponentDrivenApp *parentApp)
    : GameComponent(parentApp) {}

void SelectedTrigger::setup() {}

// Trigger Methods
bool SelectedTrigger::isActive(RenderComponent *renderComponent) {
  if (_pSet == nullptr) {
    ComponentDrivenApp *app = this->getParentApp();
    _pSet =
        app->getState<ComponentSet *>(ToggleSelectionBehaviour::stateKeyName);
  }
  // If pset has been created by a ToggleSelectionBehaviour
  if (_pSet != nullptr) {
    return _pSet->count(renderComponent) > 0;
  }

  return false;
}

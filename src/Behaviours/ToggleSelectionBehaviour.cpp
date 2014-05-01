//
//  ToggleSelectionBehaviour.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 23/04/2014.
//
//

#include "ToggleSelectionBehaviour.h"
#include <set>

ToggleSelectionBehaviour::ToggleSelectionBehaviour(GameComponent *component)
    : Behaviour(component) {}

void ToggleSelectionBehaviour::begin() {

  // cout << "ToggleSelectionBehaviour::begin()" << endl;
  _hasBegun = true;
  _elapsedTime = 0.0f;
  ComponentDrivenApp *app = _component->getParentApp();

  _pSet = app->getState<ComponentSet *>(stateKeyName);
  if (_pSet == nullptr) {
    _pSet = new ComponentSet();
    app->setState<ComponentSet *>(stateKeyName, _pSet);
  }

  if (_pSet->count(_component) > 0) {
    _pSet->erase(_component);
  } else {
    _pSet->insert(_component);
  }

  // for (auto &comp : *_pSet) {
  //  cout << "Selected component: " << comp << endl;
  //}
}

void ToggleSelectionBehaviour::update(float deltaT) { _elapsedTime += deltaT; }

void ToggleSelectionBehaviour::end() {
  // cout << "ToggleSelectionBehaviour::End() Elapsed Time: " << _elapsedTime
  //     << endl;
  _hasBegun = false;
}

bool ToggleSelectionBehaviour::hasBegun() { return _hasBegun; }

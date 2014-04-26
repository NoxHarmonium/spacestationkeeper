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

void ToggleSelectionBehaviour::Begin() {

  cout << "ToggleSelectionBehaviour::Begin()" << endl;
  _hasBegun = true;
  _elapsedTime = 0.0f;
  ComponentDrivenApp *app = _component->getParentApp();

  pSet = app->getState<ComponentSet *>(stateKeyName);
  if (pSet == nullptr) {
    pSet = new ComponentSet();
    app->setState<ComponentSet *>(stateKeyName, pSet);
  }

  if (pSet->count(_component) > 0) {
    pSet->erase(_component);
  } else {
    pSet->insert(_component);
  }

  for (auto &comp : *pSet) {
    cout << "Selected component: " << comp << endl;
  }
}

void ToggleSelectionBehaviour::Update(float deltaT) { _elapsedTime += deltaT; }

void ToggleSelectionBehaviour::End() {
  cout << "ToggleSelectionBehaviour::End() Elapsed Time: " << _elapsedTime
       << endl;
  _hasBegun = false;
}

void ToggleSelectionBehaviour::ApplyModifications(
    TransformModifierRef transformModifier,
    MaterialModifierRef materialModifier) {}

bool ToggleSelectionBehaviour::hasBegun() { return _hasBegun; }

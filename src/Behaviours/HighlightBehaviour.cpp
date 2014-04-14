//
//  HighlightBehaviour.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#include "HighlightBehaviour.h"

HighlightBehaviour::HighlightBehaviour(RenderComponent *component)
    : Behaviour(component) {}

void HighlightBehaviour::Begin() {
  cout << "Highlight::Begin()" << endl;
  _hasBegun = true;
  _elapsedTime = 0.0f;
  _component->renderEnabled =
      false; // TODO: Actually highlight rather than just disable
}

void HighlightBehaviour::Update(float deltaT) { _elapsedTime += deltaT; }

void HighlightBehaviour::End() {
  cout << "Highlight::End() Elapsed Time: " << _elapsedTime << endl;
  _hasBegun = false;
  _component->renderEnabled =
      true; // TODO: Actually highlight rather than just disable
}

bool HighlightBehaviour::hasBegun() { return _hasBegun; }

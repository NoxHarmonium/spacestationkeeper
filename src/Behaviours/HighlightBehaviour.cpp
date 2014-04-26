//
//  HighlightBehaviour.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#include "HighlightBehaviour.h"

HighlightBehaviour::HighlightBehaviour(GameComponent *component,
                                       float brightnessMultiplier,
                                       ColorAf baseColorMultiplier)
    : _brightnessMultiplier(brightnessMultiplier),
      _baseColorMultiplier(baseColorMultiplier), Behaviour(component) {}

void HighlightBehaviour::Begin() {
  cout << "Highlight::Begin()" << endl;
  _hasBegun = true;
  _elapsedTime = 0.0f;
}

void HighlightBehaviour::Update(float deltaT) { _elapsedTime += deltaT; }

void HighlightBehaviour::End() {
  cout << "Highlight::End() Elapsed Time: " << _elapsedTime << endl;
  _hasBegun = false;
}

void
HighlightBehaviour::ApplyModifications(TransformModifierRef transformModifier,
                                       MaterialModifierRef materialModifier) {
  if (_hasBegun) {
    materialModifier->addToBrightness(_brightnessMultiplier);
    materialModifier->multiplyBaseColor(_baseColorMultiplier);
  }
}

bool HighlightBehaviour::hasBegun() { return _hasBegun; }

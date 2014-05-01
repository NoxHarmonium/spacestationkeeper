//
//  HighlightBehaviour.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#include "HighlightBehaviour.h"
#include "BrightnessModifier.h"
#include "BaseColorModifier.h"

HighlightBehaviour::HighlightBehaviour(GameComponent *component,
                                       float brightnessMultiplier,
                                       ColorAf baseColorMultiplier)
    : _brightnessMultiplier(brightnessMultiplier),
      _baseColorMultiplier(baseColorMultiplier), Behaviour(component) {}

void HighlightBehaviour::begin() {
  // cout << "Highlight::begin()" << endl;
  _hasBegun = true;
  _elapsedTime = 0.0f;
}

void HighlightBehaviour::update(float deltaT) { _elapsedTime += deltaT; }

void HighlightBehaviour::end() {
  // cout << "Highlight::End() Elapsed Time: " << _elapsedTime << endl;
  _hasBegun = false;
}

vector<Modifier *> HighlightBehaviour::getModifiers() {
  vector<Modifier *> modifiers;
  if (_hasBegun) {
    modifiers.push_back(
        new BrightnessModifier(_brightnessMultiplier, ModifyMode::Multiply));
    modifiers.push_back(
        new BaseColorModifier(_baseColorMultiplier, ModifyMode::Multiply));
  }
  return modifiers;
}

bool HighlightBehaviour::hasBegun() { return _hasBegun; }

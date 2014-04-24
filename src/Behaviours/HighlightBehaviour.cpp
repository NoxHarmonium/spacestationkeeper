//
//  HighlightBehaviour.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#include "HighlightBehaviour.h"

HighlightBehaviour::HighlightBehaviour(RenderComponent *component,
                                       float brightnessModifier,
                                       ColorAf colorModifier)
    : _brightnessModifier(brightnessModifier), _colorModifier(colorModifier),
      Behaviour(component) {
  _originalBrightness = _component->material->brightness;
  _originalColor = _component->material->baseColor;
}

void HighlightBehaviour::Begin() {
  cout << "Highlight::Begin()" << endl;
  _hasBegun = true;
  _elapsedTime = 0.0f;
  _component->material->brightness = _brightnessModifier;
  _component->material->baseColor = _colorModifier;
}

void HighlightBehaviour::Update(float deltaT) { _elapsedTime += deltaT; }

void HighlightBehaviour::End() {
  cout << "Highlight::End() Elapsed Time: " << _elapsedTime << endl;
  _hasBegun = false;
  _component->material->brightness = _originalBrightness;
  _component->material->baseColor = _originalColor;
}

bool HighlightBehaviour::hasBegun() { return _hasBegun; }

//
//  MouseOverTrigger.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#include "MouseOverTrigger.h"

MouseOverTrigger::MouseOverTrigger(ComponentDrivenApp *parentApp)
    : GameComponent(parentApp) {}

// Trigger Methods
void MouseOverTrigger::RegisterBehaviour(RenderComponent *target,
                                         Behaviour *behaviour) {
  _componentMap[target].push_back(behaviour);
}

// GameComponent Methods
void MouseOverTrigger::mouseMove(MouseEvent event) {
  this->mousePoint = Vec2f(event.getX(), event.getY());
  _mouseMoved = true;
}

void MouseOverTrigger::update() {
  float delta;
  if (isnan(_lastUpdateTime)) {
    delta = 0.0f;
  } else {
    delta = ci::app::getElapsedSeconds() - _lastUpdateTime;
  }

  _lastUpdateTime = ci::app::getElapsedSeconds();

  for (auto &pair : _componentMap) {
    RenderComponent *c = pair.first;
    vector<Behaviour *> behaviours = pair.second;
    AxisAlignedBox3f bounds = c->getBounds();

    // cout << "Bounds: " << bounds.getCenter() << "Mouse: " << mousePoint <<
    // endl;
    if (Utils::isInside(bounds, mousePoint)) {

      for (auto &behaviour : behaviours) {
        if (!behaviour->hasBegun()) {
          behaviour->Begin();
        } else {
          behaviour->Update(delta); // todo delta time
        }
      }
    } else {
      for (auto &behaviour : behaviours) {
        if (behaviour->hasBegun()) {
          behaviour->End();
        }
      }
    }

    _mouseMoved = false;
  }
}

//
//  MouseClickTrigger.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 23/04/2014.
//
//

#include "MouseClickTrigger.h"

MouseClickTrigger::MouseClickTrigger(ComponentDrivenApp *parentApp)
    : GameComponent(parentApp) {
  this->mouseDownPoint = Vec2f(0.0f, 0.0f);
  cout << "MouseClickTrigger constructed!" << endl;
}

// Trigger Methods
bool MouseClickTrigger::isActive(RenderComponent *renderComponent) {
  AxisAlignedBox3f bounds = renderComponent->getBounds();
  // Cache this call for all mouse events (i.e. click needs same information as
  // over)

  // cout << "Mouse moved to: " << this->mousePoint << " center "
  //     << bounds.getCenter() << endl;
  if (doClickTrigger) {
    clickTriggered = true;
    return Utils::isInside(bounds, this->mouseUpPoint);
  } else {
    return false;
  }
}

void MouseClickTrigger::mouseDown(MouseEvent event) {
  this->mouseDownPoint = Vec2f(event.getX(), event.getY());
  this->mouseDownTime = ci::app::getElapsedSeconds();
}
void MouseClickTrigger::mouseUp(MouseEvent event) {
  this->mouseUpPoint = Vec2f(event.getX(), event.getY());
  float mouseDistance = mouseUpPoint.distance(this->mouseDownPoint);
  float mouseDownDuration = ci::app::getElapsedSeconds() - this->mouseDownTime;
  cout << "mouseDistance: " << mouseDistance
       << " mouseDownDuration: " << mouseDownDuration << endl;

  if (mouseDistance < MouseClickTrigger::moveThreshold &&
      mouseDownDuration < MouseClickTrigger::timeThreshold) {
    doClickTrigger = true;
  }
}

void MouseClickTrigger::update() {
  if (clickTriggered) {
    doClickTrigger = false;
    clickTriggered = false;
  }
}

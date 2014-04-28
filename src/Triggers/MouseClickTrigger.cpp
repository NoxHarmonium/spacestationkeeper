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
  this->_mouseDownPoint = Vec2f(0.0f, 0.0f);
  cout << "MouseClickTrigger constructed!" << endl;
}

// Trigger Methods
bool MouseClickTrigger::isActive(RenderComponent *renderComponent) {
  AxisAlignedBox3f bounds = renderComponent->getBounds();
  // Cache this call for all mouse events (i.e. click needs same information as
  // over)

  // cout << "Mouse moved to: " << this->mousePoint << " center "
  //     << bounds.getCenter() << endl;
  if (this->_doClickTrigger) {
    this->_clickTriggered = true;
    return Utils::isInside(bounds, this->_mouseUpPoint);
  } else {
    return false;
  }
}

void MouseClickTrigger::mouseDown(MouseEvent event) {
  this->_mouseDownPoint = Vec2f(event.getX(), event.getY());
  this->_mouseDownTime = ci::app::getElapsedSeconds();
}
void MouseClickTrigger::mouseUp(MouseEvent event) {
  this->_mouseUpPoint = Vec2f(event.getX(), event.getY());
  float mouseDistance = _mouseUpPoint.distance(this->_mouseDownPoint);
  float mouseDownDuration = ci::app::getElapsedSeconds() - this->_mouseDownTime;
  cout << "mouseDistance: " << mouseDistance
       << " mouseDownDuration: " << mouseDownDuration << endl;

  if (mouseDistance < MouseClickTrigger::moveThreshold &&
      mouseDownDuration < MouseClickTrigger::timeThreshold) {
    _doClickTrigger = true;
  }
}

void MouseClickTrigger::update() {
  if (_clickTriggered) {
    _doClickTrigger = false;
    _clickTriggered = false;
  }
}

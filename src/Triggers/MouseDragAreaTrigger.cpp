//
//  MouseDragAreaTrigger.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/05/2014.
//
//

#include "MouseDragAreaTrigger.h"

MouseDragAreaTrigger::MouseDragAreaTrigger(ComponentDrivenApp *parentApp,
                                           bool triggerOnRelease)
    : GameComponent(parentApp) {
  _mouseDownPoint = Vec2f(0.0f, 0.0f);
  _triggerOnRelease = triggerOnRelease;
  cout << "MouseDragAreaTrigger constructed!" << endl;
}

// Trigger Methods
bool MouseDragAreaTrigger::isActive(RenderComponent *renderComponent) {
  AxisAlignedBox3f bounds = renderComponent->getBounds();
  // TODO: Cache this call for all mouse events (i.e. click needs same
  // information as
  // over)

  // cout << "Mouse moved to: " << this->mousePoint << " center "
  //     << bounds.getCenter() << endl;
  if (this->_doDragTrigger && (!_triggerOnRelease || !_mouseDown)) {
    if (_triggerOnRelease) {
      _triggered = true;
    }

    return Utils::areOverlapping(bounds, _dragArea);
  } else {
    return false;
  }
}

void MouseDragAreaTrigger::mouseDown(MouseEvent event) {
  this->_mouseDownPoint = Vec2f(event.getX(), event.getY());
  this->_mouseDownTime = ci::app::getElapsedSeconds();
  _mouseDown = true;
  _triggered = false;
}
void MouseDragAreaTrigger::mouseUp(MouseEvent event) { _mouseDown = false; }

void MouseDragAreaTrigger::mouseDrag(MouseEvent event) {
  _currentMousePoint = Vec2f(event.getX(), event.getY());
}

void MouseDragAreaTrigger::update() {
  if (_triggered) {
    _doDragTrigger = false;
  }

  if (_mouseDown) {
    float mouseDistance = _currentMousePoint.distance(this->_mouseDownPoint);
    float mouseDownDuration =
        ci::app::getElapsedSeconds() - this->_mouseDownTime;

    // cout << "mouseDistance: " << mouseDistance
    //     << " mouseDownDuration: " << mouseDownDuration
    //     << " currentMousePoint: " << _currentMousePoint
    //     << " mouseDownPoint: " << _mouseDownPoint << endl;

    if (_doDragTrigger ||
        (mouseDistance > MouseDragAreaTrigger::moveThreshold &&
         mouseDownDuration > MouseDragAreaTrigger::timeThreshold)) {
      _doDragTrigger = true;

      float x1 = min(_mouseDownPoint.x, _currentMousePoint.x);
      float x2 = max(_mouseDownPoint.x, _currentMousePoint.x);
      float y1 = min(_mouseDownPoint.y, _currentMousePoint.y);
      float y2 = max(_mouseDownPoint.y, _currentMousePoint.y);

      _dragArea = Rectf(x1, y1, x2, y2);
    }
  } else {
    if (!_triggerOnRelease) {
      _doDragTrigger = false;
    }
  }
}

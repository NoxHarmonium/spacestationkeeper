//
//  MouseOverTrigger.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#include "MouseOverTrigger.h"

MouseOverTrigger::MouseOverTrigger(ComponentDrivenApp *parentApp)
    : GameComponent(parentApp) {
  this->mousePoint = Vec2f(0.0f, 0.0f);
  cout << "MouseOverTrigger constructed!" << endl;
}

// Trigger Methods
bool MouseOverTrigger::isActive(RenderComponent *renderComponent) {
  AxisAlignedBox3f bounds = renderComponent->getBounds();
  // Cache this call for all mouse events (i.e. click needs same information as
  // over)

  // cout << "Mouse moved to: " << this->mousePoint << " center "
  //     << bounds.getCenter() << endl;
  return Utils::isInside(bounds, this->mousePoint);
}

// GameComponent Methods
void MouseOverTrigger::mouseMove(MouseEvent event) {
  this->mousePoint = Vec2f(event.getX(), event.getY());
}

void MouseOverTrigger::update() {
  /*
     */
}

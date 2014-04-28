//
//  MouseOverTrigger.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#ifndef SpaceStationKeeper_MouseClickTrigger_cpp
#define SpaceStationKeeper_MouseClickTrigger_cpp

#include <map>
#include "Trigger.h"
#include "GameComponent.h"
#include "Utils.h"

class MouseClickTrigger : public Trigger, public GameComponent {
public:
  static constexpr float moveThreshold = 10.0f;
  static constexpr float timeThreshold = 10.0f;

  MouseClickTrigger(ComponentDrivenApp *parentApp);

  bool isActive(RenderComponent *renderComponent);

  // GameComponent Methods
  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void update();

private:
  Vec2f _mouseDownPoint;
  Vec2f _mouseUpPoint;
  bool _doClickTrigger = false;
  bool _clickTriggered = false;
  float _mouseDownTime = 0.0f;
};

#endif

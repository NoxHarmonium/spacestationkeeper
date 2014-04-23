//
//  MouseOverTrigger.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 14/04/2014.
//
//

#ifndef SpaceStationKeeper_MouseOverTrigger_cpp
#define SpaceStationKeeper_MouseOverTrigger_cpp

#include <map>
#include "Trigger.h"
#include "GameComponent.h"
#include "Utils.h"

class MouseOverTrigger : public Trigger, public GameComponent {
public:
  MouseOverTrigger(ComponentDrivenApp *parentApp);

  bool isActive(RenderComponent *renderComponent);

  // GameComponent Methods
  void mouseMove(MouseEvent event);
  void update();

private:
  Vec2f mousePoint;
};

#endif

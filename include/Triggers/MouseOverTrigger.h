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

  // Trigger Methods
  void RegisterBehaviour(RenderComponent *target, Behaviour *behaviour);

  // GameComponent Methods
  void mouseMove(MouseEvent event);
  void update();

private:
  map<RenderComponent *, vector<Behaviour *>> _componentMap;
  Vec2f mousePoint;
  bool _mouseMoved = false;
  float _lastUpdateTime = NAN;
};

#endif

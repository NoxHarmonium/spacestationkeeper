//
//  TriggeredRenderComponent.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_TriggeredRenderComponent_h
#define SpaceStationKeeper_TriggeredRenderComponent_h

#include "RenderComponent.h"
#include "EventManager.h"

class TriggeredRenderComponent : public RenderComponent {
public:
  TriggeredRenderComponent(ComponentDrivenApp *parent)
      : RenderComponent(parent) {};
  void setEventManager(EventManager *eventManager) {
    _eventManager = eventManager;
  }

  void update();

protected:
  virtual RenderInfo *getRenderInfo();

  EventManager *getEventManager() { return _eventManager; }

private:
  RenderInfo *_modifiedRenderInfo = nullptr;
  EventManager *_eventManager;
  vector<Modifier *> _modifiers;
};

#endif

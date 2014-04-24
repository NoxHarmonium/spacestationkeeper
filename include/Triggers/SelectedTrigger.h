//
//  SelectedTrigger.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/04/2014.
//
//

#ifndef SpaceStationKeeper_SelectedTrigger_h
#define SpaceStationKeeper_SelectedTrigger_h

#include "Trigger.h"
#include "ToggleSelectionBehaviour.h"

class SelectedTrigger : public Trigger, public GameComponent {
public:
  SelectedTrigger(ComponentDrivenApp *parentApp);

  void setup();

  bool isActive(RenderComponent *renderComponent);

private:
  ComponentSet *_pSet = nullptr;
};

#endif

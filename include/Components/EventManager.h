//
//  EventManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 22/04/2014.
//
//

#ifndef SpaceStationKeeper_EventManager_h
#define SpaceStationKeeper_EventManager_h

#include <stdlib.h>
#include "RenderComponent.h"
#include "Behaviour.h"
#include "BehaviourConstructor.h"
#include "Trigger.h"

struct EventRegistration {
  string eventName;
  string classPattern;
  BehaviourConstructor *behaviourConstructor;
  map<RenderComponent *, Behaviour *> constructedBehaviours;
};

class EventManager : public GameComponent {
public:
  EventManager(ComponentDrivenApp *parent);

  // Register an available event associated with a given trigger.
  void RegisterEvent(string eventName, Trigger *trigger);
  // Subscribe a whole class of components to an event. The special
  // BehaviourConstructor class is needed to instantiate a new instance of a
  // behaviour for a variable number of components.
  void SubscribeBehavior(string eventName, string classPattern,
                         BehaviourConstructor *BehaviourConstructor);
  // Subscribe a single component to an event with a provided instance of a
  // behaviour
  void SuscribeBehaviour(string eventName, RenderComponent *renderComponent,
                         Behaviour *behaviour);

  vector<Modifier *> ProcessTriggers(RenderComponent *renderComponent);

  // Component events
  void update();

private:
  void processTriggers(RenderComponent *renderComponent,
                       vector<EventRegistration *> eventRegistration,
                       vector<Modifier *> *modifiers);

  void handleBehaviour(RenderComponent *renderComponent, Trigger *trigger,
                       Behaviour *behaviour, vector<Modifier *> *modifiers);

  float _lastUpdateTime = NAN;
  float _deltaTime = 0.0f;
  map<RenderComponent *, vector<pair<Trigger *, vector<Behaviour *>>>>
  _componentMap;

  map<string, vector<EventRegistration *>> _classFilterMap;

  map<string, Trigger *> _triggerMap;
};

typedef std::shared_ptr<EventManager> EventManagerRef;

#endif

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
#include "GameComponent.h"
#include "Behaviour.h"
#include "BehaviourConstructor.h"
#include "Trigger.h"
#include "TransformModifier.h"
#include "MaterialModifier.h"

struct EventRegistration {
  string eventName;
  string classPattern;
  BehaviourConstructor *behaviourConstructor;
  map<GameComponent *, Behaviour *> constructedBehaviours;
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
  void SuscribeBehaviour(string eventName, GameComponent *renderComponent,
                         Behaviour *behaviour);

  void ProcessTriggers(GameComponent *renderComponent,
                       TransformModifierRef transformModifier,
                       MaterialModifierRef materialModifier);

  // Component events
  void update();

private:
  void processTriggers(GameComponent *renderComponent,
                       vector<EventRegistration *> eventRegistration,
                       TransformModifierRef transformModifier,
                       MaterialModifierRef materialModifier);

  void handleBehaviour(GameComponent *renderComponent, Trigger *trigger,
                       Behaviour *behaviour,
                       TransformModifierRef transformModifier,
                       MaterialModifierRef materialModifier);

  float _lastUpdateTime = NAN;
  float _deltaTime = 0.0f;
  map<GameComponent *, vector<pair<Trigger *, vector<Behaviour *>>>>
  _componentMap;

  map<string, vector<EventRegistration *>> _classFilterMap;

  map<string, Trigger *> _triggerMap;
};

typedef std::shared_ptr<EventManager> EventManagerRef;

#endif

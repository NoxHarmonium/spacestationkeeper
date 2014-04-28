//
//  EventManager.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 22/04/2014.
//
//

#include "EventManager.h"

EventManager::EventManager(ComponentDrivenApp *parent)
    : GameComponent(parent) {}

// Register an available event associated with a given trigger.
void EventManager::registerEvent(string eventName, Trigger *trigger) {
  if (_triggerMap.count(eventName) != 0) {
    cout << "Warning: eventName: " << eventName
         << " already registered with a trigger. It will be "
            "overwritten." << endl;
  }
  _triggerMap[eventName] = trigger;
}

// Subscribe a whole class of components to an event. The special
// BehaviourConstructor class is needed to instantiate a new instance of a
// behaviour for a variable number of components.
void
EventManager::subscribeBehavior(string eventName, string classPattern,
                                BehaviourConstructor *behaviourConstructor) {

  EventRegistration *reg = new EventRegistration();
  reg->eventName = eventName;
  reg->classPattern = classPattern;
  reg->behaviourConstructor = behaviourConstructor;

  _classFilterMap[classPattern].push_back(reg);
}

// Subscribe a single component to an event with a provided instance of a
// behaviour
void EventManager::suscribeBehaviour(string eventName,
                                     RenderComponent *renderComponent,
                                     Behaviour *behaviour) {}

vector<Modifier *>
EventManager::processTriggers(RenderComponent *renderComponent) {
  vector<Modifier *> modifiers;
  // TODO: Passing the modifiers around like that, its terrible I need to re
  // think the way it all works
  if (_componentMap.count(renderComponent)) {
    for (auto &pair : _componentMap[renderComponent]) {
      for (auto &behaviour : pair.second) {
        handleBehaviour(renderComponent, pair.first, behaviour, &modifiers);
      }
    }
  }

  if (renderComponent->classFilter.length() > 0 &&
      _classFilterMap.count(renderComponent->classFilter)) {
    processTriggers(renderComponent,
                    _classFilterMap[renderComponent->classFilter], &modifiers);
  }

  return modifiers;
}

// Component events
void EventManager::update() {

  if (isnan(_lastUpdateTime)) {
    _deltaTime = 0.0f;
  } else {
    _deltaTime = ci::app::getElapsedSeconds() - _lastUpdateTime;
  }

  _lastUpdateTime = ci::app::getElapsedSeconds();
}

void
EventManager::processTriggers(RenderComponent *renderComponent,
                              vector<EventRegistration *> eventRegistrations,
                              vector<Modifier *> *modifiers) {

  for (auto &eventReg : eventRegistrations) {
    Trigger *trigger = _triggerMap[eventReg->eventName];

    if (trigger == nullptr) {
      cout << "Event name: " << eventReg->eventName << " is not registered."
           << endl;
      throw new std::exception();
    }

    Behaviour *behaviour = eventReg->constructedBehaviours[renderComponent];
    if (behaviour == nullptr) {
      behaviour = eventReg->behaviourConstructor->Construct(renderComponent);
      eventReg->constructedBehaviours[renderComponent] = behaviour;
    }
    handleBehaviour(renderComponent, trigger, behaviour, modifiers);
  }
}

void EventManager::handleBehaviour(RenderComponent *renderComponent,
                                   Trigger *trigger, Behaviour *behaviour,
                                   vector<Modifier *> *modifiers) {
  if (trigger->isActive(renderComponent)) {
    if (!behaviour->hasBegun()) {
      behaviour->begin();
    } else {
      behaviour->update(_deltaTime); // todo delta time
    }
  } else {
    if (behaviour->hasBegun()) {
      behaviour->end();
    }
  }

  for (auto &mod : behaviour->getModifiers()) {
    modifiers->push_back(mod);
  }
}
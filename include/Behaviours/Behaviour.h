//
//  Behviour.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 13/04/2014.
//
//

#ifndef SpaceStationKeeper_Behaviour_h
#define SpaceStationKeeper_Behaviour_h

#include "GameComponent.h"
#include "Modifier.h"

class Behaviour {
public:
  Behaviour(GameComponent *component) : _component(component) {};
  virtual ~Behaviour() {};

  virtual void Begin() = 0;
  virtual void Update(float deltaT) = 0;
  virtual void End() = 0;
  virtual vector<Modifier *> GetModifiers() = 0;

  virtual bool hasBegun() = 0;

protected:
  GameComponent *_component = nullptr;
};

#endif

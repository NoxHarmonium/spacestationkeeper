//
//  Behviour.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 13/04/2014.
//
//

#ifndef SpaceStationKeeper_Behaviour_h
#define SpaceStationKeeper_Behaviour_h

#include "RenderComponent.h"

class Behaviour {
public:
  Behaviour(RenderComponent *component) : _component(component) {};

  virtual void Begin() = 0;
  virtual void Update(float deltaT) = 0;
  virtual void End() = 0;

  virtual bool hasBegun() = 0;

protected:
  RenderComponent *_component = nullptr;
};

#endif

//
//  ToggleSelectionBehaviour.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 23/04/2014.
//
//

#ifndef SpaceStationKeeper_ToggleSelectionBehaviour_h
#define SpaceStationKeeper_ToggleSelectionBehaviour_h

#include "Behaviour.h"
#include <set>

typedef set<GameComponent *> ComponentSet;

class ToggleSelectionBehaviour : public Behaviour {
public:
  static constexpr char *stateKeyName = "selectedComponents";

  ToggleSelectionBehaviour(GameComponent *component);
  ~ToggleSelectionBehaviour() {};

  void Begin();
  void Update(float deltaT);
  void End();
  vector<Modifier *> GetModifiers() { return vector<Modifier *>(); }

  bool hasBegun();

private:
  bool _hasBegun = false;
  float _elapsedTime = 0.0f;
  ComponentSet *pSet = nullptr;
};

#endif

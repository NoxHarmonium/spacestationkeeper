//
//  BehaviourConstructor.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 22/04/2014.
//
//

#ifndef SpaceStationKeeper_BehaviourConstructor_h
#define SpaceStationKeeper_BehaviourConstructor_h

#include "pch.h"
#include <functional>
#include "Behaviour.h"

typedef std::function<Behaviour *(GameComponent *)> constructorFn;

// A complicated way to create an object that constructs a specific type of
// behaviour on demand
class BehaviourConstructor {
public:
  Behaviour *Construct(GameComponent *renderComponent) {
    return _constFn(renderComponent);
  }

  // template <typename T> std::shared_ptr<T> loadAsset(string assetRef)

  template <typename T> static BehaviourConstructor *Create() {
    constructorFn lambda = [](GameComponent *gameComponent) {
      return dynamic_cast<Behaviour *>(new T(gameComponent));
    };

    return new BehaviourConstructor(lambda);
  }

  template <typename T, typename... Args>
  static BehaviourConstructor *Create(Args... args) {
    constructorFn lambda = [args...](GameComponent * gameComponent)->Behaviour *
    {
      return dynamic_cast<Behaviour *>(new T(gameComponent, args...));
    };

    return new BehaviourConstructor(lambda);
  }

private:
  BehaviourConstructor(constructorFn constFn) { _constFn = constFn; }
  constructorFn _constFn;
};

#endif

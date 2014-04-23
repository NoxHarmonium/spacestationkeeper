//
//  BehaviourConstructor.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 22/04/2014.
//
//

#ifndef SpaceStationKeeper_BehaviourConstructor_h
#define SpaceStationKeeper_BehaviourConstructor_h

#include <stdlib.h>
// A complicated way to create an object that constructs a specific type of
// behaviour on demand
class BehaviourConstructor {
public:
  Behaviour *Construct(RenderComponent *renderComponent) {
    return _constFn(renderComponent);
  }

  // template <typename T> std::shared_ptr<T> LoadAsset(string assetRef)

  template <typename T> static BehaviourConstructor *Create() {
    auto lambda = [](RenderComponent *renderComponent) {
      return dynamic_cast<Behaviour *>(new T(renderComponent));
    };

    return new BehaviourConstructor(lambda);
  }

private:
  BehaviourConstructor(Behaviour *constFn(RenderComponent *)) {
    _constFn = constFn;
  }
  Behaviour *(*_constFn)(RenderComponent *);
};

#endif

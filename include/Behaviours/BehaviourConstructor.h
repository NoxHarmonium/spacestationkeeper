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

typedef std::function<Behaviour *(RenderComponent *)> constructorFn;

// A complicated way to create an object that constructs a specific type of
// behaviour on demand
class BehaviourConstructor {
public:
  Behaviour *Construct(RenderComponent *renderComponent) {
    return _constFn(renderComponent);
  }

  // template <typename T> std::shared_ptr<T> LoadAsset(string assetRef)

  template <typename T> static BehaviourConstructor *Create() {
    constructorFn lambda = [](RenderComponent *renderComponent) {
      return dynamic_cast<Behaviour *>(new T(renderComponent));
    };

    return new BehaviourConstructor(lambda);
  }

  template <typename T, typename... Args>
  static BehaviourConstructor *Create(Args... args) {
    constructorFn lambda = [args...](RenderComponent * renderComponent)
                               ->Behaviour *
    {
      return dynamic_cast<Behaviour *>(new T(renderComponent, args...));
    };

    return new BehaviourConstructor(lambda);
  }

private:
  BehaviourConstructor(constructorFn constFn) { _constFn = constFn; }
  constructorFn _constFn;
};

#endif

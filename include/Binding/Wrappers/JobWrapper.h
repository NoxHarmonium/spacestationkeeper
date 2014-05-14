//
//  JobWrapper.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 13/05/2014.
//
//

#ifndef SpaceStationKeeper_JobWrapper_h
#define SpaceStationKeeper_JobWrapper_h

struct JobWrapper : public Job, public luabind::wrap_base {
  JobWrapper() : Job() {}
  // Call registers
  virtual bool preRequisitesAreMet() {
    return call<bool>("preRequisitesAreMet");
  };

  virtual bool postRequistesAreMet() {
    return call<bool>("postRequistesAreMet");
  };

  virtual bool isDone() {
    return call<bool>("isDone");
  };

  virtual float getProgress() {
    return call<float>("getProgress");
  };

  virtual void update(float deltaTime) {
    call<void>("update", deltaTime);
  };

  virtual void assignResources(ResourceAllocation allocation) {
    call<void>("assignResources", allocation);
  };

  virtual void removeResources(ResourceAllocation allocation) {
    call<void>("removeResources", allocation);
  };

  virtual ResourceAllocation getResourceAllocation() {
    return call<ResourceAllocation>("getResourceAllocation");
  };
};

#endif

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
  virtual bool preRequisitesAreMet() override {
    return call<bool>("preRequisitesAreMet");
  };

  virtual bool postRequistesAreMet() override {
    return call<bool>("postRequistesAreMet");
  };

  virtual bool isDone() override {
    return call<bool>("isDone");
  };

  virtual float getProgress() override {
    return call<float>("getProgress");
  };

  virtual void update(float deltaTime) override {
    call<void>("update", deltaTime);
  };

  virtual ci::Vec2i getStartLocation() override {
    return call<ci::Vec2i>("getStartLocation");
  };

  virtual ci::Vec2i getEndLocation() override {
    return call<ci::Vec2i>("getEndLocation");
  };

  virtual int getRadius() override {
    return call<int>("getRadius");
  };
};

#endif

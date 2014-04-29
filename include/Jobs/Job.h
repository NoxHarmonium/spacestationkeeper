//
//  Job.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/04/2014.
//
//

#ifndef SpaceStationKeeper_Job_h
#define SpaceStationKeeper_Job_h

typedef map<Resource, int> ResourceAlloction;

class Job {
public:
  virtual bool preRequisitesAreMet() = 0;
  virtual bool postRequistesAreMet() = 0;
  virtual bool isDone() = 0;
  virtual float getProgress() = 0;
  virtual void update(float deltaTime) = 0;

  void assignResources(ResourceAlloction allocation);
  void removeResources(ResourceAlloction allocation);
  ResourceAlloction getResourceAllocation();

private:
  ResourceAlloction _resources;
};

#endif

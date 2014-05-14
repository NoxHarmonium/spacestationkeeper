//
//  Job.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/04/2014.
//
//

#ifndef SpaceStationKeeper_Job_h
#define SpaceStationKeeper_Job_h

#include "Resource.h"

using namespace std;

typedef map<Resource *, int> ResourceAllocation;

class Job {
public:
  Job() {};
  virtual ~Job() {};

  virtual bool preRequisitesAreMet() = 0;
  virtual bool postRequistesAreMet() = 0;
  virtual bool isDone() = 0;
  virtual float getProgress() = 0;
  virtual void update(float deltaTime) = 0;

  void assignResources(ResourceAllocation allocation);
  void removeResources(ResourceAllocation allocation);
  ResourceAllocation getResourceAllocation();

private:
  ResourceAllocation _resources;
};

typedef std::shared_ptr<Job> JobRef;

#endif

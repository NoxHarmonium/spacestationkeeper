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
#include <vector>
#include <memory>

using namespace std;
using namespace ci;

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
  virtual Vec2i getStartLocation() = 0;
  virtual Vec2i getEndLocation() = 0;
  virtual int getRadius() { return 0; }
  virtual Vec2f getWorkerSlot(int workerIndex) = 0;
  virtual int getMaxWorkers() = 0;

  void allocateWorker();
  void deallocateWorker();
  int getWorkerCount();
  void activateWorker();
  void deactivateWorker();
  int getActiveWorkers();

  void assignResources(ResourceAllocation allocation);
  void removeResources(ResourceAllocation allocation);
  ResourceAllocation getResourceAllocation();

private:
  ResourceAllocation _resources;
  int _workerCount = 0;
  int _activeWorkerCount = 0;
};

typedef std::shared_ptr<Job> JobRef;

#endif

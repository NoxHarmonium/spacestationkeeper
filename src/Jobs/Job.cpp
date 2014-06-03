//
//  Job.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/04/2014.
//
//

#include <map>
#include "Resource.h"
#include "Job.h"
#include <stdexcept>

void Job::allocateWorker() {
  _workerCount++;
  if (_workerCount > getMaxWorkers()) {
    throw runtime_error("Allocated more workers than allowed.");
  }
}

void Job::deallocateWorker() {
  _workerCount--;
  if (_workerCount < 0) {
    throw runtime_error("Allocated less workers than 0.");
  }
}

int Job::getWorkerCount() { return _workerCount; }

void Job::assignResources(ResourceAllocation allocation) {
  for (auto &kvp : allocation) {
    _resources[kvp.first] += kvp.second;
  }
}

void Job::removeResources(ResourceAllocation allocation) {
  for (auto &kvp : allocation) {
    _resources[kvp.first] -= kvp.second;
    assert(_resources[kvp.first] >= 0);
  }
}

ResourceAllocation Job::getResourceAllocation() { return _resources; }

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

namespace BlazeEngine {
namespace Jobs {

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

void Job::activateWorker() {
  _activeWorkerCount++;
  if (_activeWorkerCount > _workerCount) {
    throw runtime_error(
        "Activated more workers than are allocated to this job.");
  }
}
void Job::deactivateWorker() {
  _activeWorkerCount--;
  if (_activeWorkerCount < 0) {
    throw runtime_error(
        "Deactivated more workers than are allocated to this job.");
  }
}
int Job::getActiveWorkers() { return _activeWorkerCount; }
}
}

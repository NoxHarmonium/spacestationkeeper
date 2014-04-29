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

void Job::assignResources(ResourceAllocation allocation) {
  for (auto &kvp : allocation) {
    _resources[kvp.first] += kvp.second;
  }
}

void Job::removeResources(ResourceAllocation allocation) {
  for (auto &kvp : allocation) {
    _resources[kvp.first] -= kvp.second;
  }
}

ResourceAllocation Job::getResourceAllocation() { return _resources; }

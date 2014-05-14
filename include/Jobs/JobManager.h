//
//  JobManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 29/04/2014.
//
//

#ifndef SpaceStationKeeper_JobManager_h
#define SpaceStationKeeper_JobManager_h

#include "Job.h"

enum JobState { Pending, Running, Finished, Cancelled };

class JobManager {
public:
  JobManager() {};
  ~JobManager() {}

  void update();
  void registerJob(JobRef job);
  void cancelJob(JobRef job);

private:
  map<JobRef, JobState> _registeredJobs;
};

#endif

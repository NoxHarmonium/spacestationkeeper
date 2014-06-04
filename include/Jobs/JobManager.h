//
//  JobManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 29/04/2014.
//
//

#ifndef SpaceStationKeeper_JobManager_h
#define SpaceStationKeeper_JobManager_h

#include "GameComponent.h"
#include "Job.h"

enum JobState { Pending, Running, Finished, Cancelled };

class JobManager : public GameComponent {
public:
  // Constructors/Destructors
  JobManager() {};
  ~JobManager() {}

  // Getters/Setters
  vector<JobRef> getActiveJobs(bool filterFullJobs);

  // Methods
  void registerJob(JobRef job);
  void cancelJob(JobRef job);

  // GameComponent Methods
  virtual void update(float deltaTime) override;

private:
  map<JobRef, JobState> _registeredJobs;
};

typedef std::shared_ptr<JobManager> JobManagerRef;

#endif

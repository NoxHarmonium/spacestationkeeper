//
//  JobManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 29/04/2014.
//
//

#ifndef SpaceStationKeeper_JobManager_h
#define SpaceStationKeeper_JobManager_h

enum JobState { Pending, Running, Finished, Cancelled };

class JobManager : public GameComponent {
public:
  JobManager(ComponentDrivenApp *parent) : GameComponent(parent) {};
  ~JobManager() {}

  void update();
  void registerJob(JobRef job);
  void cancelJob(JobRef job);

private:
  map<JobRef, JobState> _registeredJobs;
};

#endif

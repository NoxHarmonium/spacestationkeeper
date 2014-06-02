//
//  JobManager.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 29/04/2014.
//
//

#include "GameComponent.h"
#include "Resource.h"
#include "Job.h"
#include "JobManager.h"
#include "ComponentDrivenApp.h"

void JobManager::update(float deltaTime) {
  map<JobRef, JobState> jobMapCopy = _registeredJobs;

  for (auto &kvp : jobMapCopy) {
    JobRef job = kvp.first;
    JobState state = kvp.second;

    switch (state) {
    case JobState::Pending:
      if (job->preRequisitesAreMet()) {
        cout << "JobManager::update(): Switching pending job to running..."
             << endl;
        _registeredJobs[job] = JobState::Running;
      }
      break;
    case JobState::Running:
      job->update(deltaTime);
      if (job->isDone()) {
        cout << "JobManager::update(): Switching running job to finished..."
             << endl;
        assert(job->postRequistesAreMet());
        _registeredJobs[job] = JobState::Finished;
      }
      break;

    case JobState::Cancelled:
      // TODO: job->cancel/cleanup

      _registeredJobs[job] = JobState::Finished;
      break;

    case JobState::Finished:
      _registeredJobs.erase(job);
      break;

    default:
      break;
    }
  }
}
void JobManager::registerJob(JobRef job) {
  _registeredJobs[job] = JobState::Pending;
}
void JobManager::cancelJob(JobRef job) {
  if (_registeredJobs.count(job)) {
    _registeredJobs[job] = JobState::Cancelled;
  }
}

vector<JobRef> JobManager::getPendingJobs() {
  vector<JobRef> pendingJobs;
  for (auto &kvp : _registeredJobs) {
    JobRef job = kvp.first;
    JobState state = kvp.second;
    if (state == JobState::Pending) {
      pendingJobs.push_back(job);
    }
  }
  return pendingJobs;
}

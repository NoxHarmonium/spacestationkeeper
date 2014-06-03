//
//  JobBinder.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 13/05/2014.
//
//

#ifndef SpaceStationKeeper_JobBinder_h
#define SpaceStationKeeper_JobBinder_h

#include "ClassBinder.h"
#include "Job.h"
#include "JobWrapper.h"

template <> struct ClassBinder<Job> {
  // Game component can be inherited from in LUA to make components so it is
  // special and has a wrapper

  static void Bind(const char *name, lua_State *L) {
    luabind::module(
        L)[luabind::class_<Job, JobWrapper, JobRef>(name)
               .def(luabind::constructor<>())
               .def("preRequisitesAreMet", &Job::preRequisitesAreMet)
               .def("postRequistesAreMet", &Job::postRequistesAreMet)
               .def("isDone", &Job::isDone)
               .def("getProgress", &Job::getProgress)
               .def("update", &Job::update)
               .def("assignResources", &Job::assignResources)
               .def("removeResources", &Job::removeResources)
               .def("getRadius", &Job::getRadius)
               .def("getResourceAllocation", &Job::getResourceAllocation)
               .def("getStartLocation", &Job::getStartLocation)
               .def("getEndLocation", &Job::getEndLocation)
               .def("allocateWorker", &Job::allocateWorker)
               .def("deallocateWorker", &Job::deallocateWorker)
               .def("getWorkerCount", &Job::getWorkerCount)];
  }
};

#endif

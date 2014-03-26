//
//  Utils.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "Utils.h"

std::string Utils::getCurrentExecutablePath() {
#if defined __APPLE__ && __MACH__
  // Thanks: http://stackoverflow.com/a/8149380/1153203

  int ret;
  pid_t pid;
  char pathbuf[PROC_PIDPATHINFO_MAXSIZE];

  pid = getpid();
  ret = proc_pidpath(pid, pathbuf, sizeof(pathbuf));
  if (ret <= 0) {
    fprintf(stderr, "PID %d: proc_pidpath ();\n", pid);
    fprintf(stderr, "    %s\n", strerror(errno));
    throw new std::exception(); // Error getting path
  } else {
    return std::string(pathbuf);
  }

#else

  // TODO: Implement other OS
  throw new std::exception();

#endif
}
//
//  Utils.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "Utils.h"

using namespace boost;

filesystem::path Utils::getCurrentExecutablePath() {
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
    return filesystem::path(pathbuf);
  }

#else
  // TODO: Implement other OS
  throw new std::exception();
#endif
}

filesystem::path Utils::getResourcesPath() {
#if defined __APPLE__ && __MACH__
  return getCurrentExecutablePath().parent_path() /
         filesystem::path(OSX_RESOURCE_DIR);
#else
  // TODO: Implement other OS
  throw new std::exception();
#endif
}

std::string Utils::strToUpper(std::string inputString) {
  std::string s = std::string(inputString);
  for (auto &c : s)
    c = toupper(c);
  return s;
}

BOOL Utils::existsIn(std::string sourceString, std::string searchString) {
  return strToUpper(sourceString).find(strToUpper(searchString)) !=
         std::string::npos;
}

bool Utils::isInside(ci::AxisAlignedBox3f bounds, ci::Vec2f point) {
  return (point.x > bounds.getMin().x && point.x < bounds.getMax().x &&
          point.y > bounds.getMin().y && point.y < bounds.getMax().y);
}

bool Utils::isInside(ci::AxisAlignedBox3f bounds, ci::Vec3f point) {
  return (Utils::isInside(bounds, point) && point.z > bounds.getMin().z &&
          point.z < bounds.getMax().z);
}

void Utils::printOpenGlVersionInfo() {

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *vendor = glGetString(GL_VENDOR);
  const GLubyte *version = glGetString(GL_VERSION);
  const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
  // GLint major, minor; // TODO: Can't work out where the OpenGL constants are.
  // glGetIntegerv(GL_MAJOR_VERSION, &major);
  // glGetIntegerv(GL_MINOR_VERSION, &minor);
  printf("\nOpenGL Version Info:\n");
  printf("GL Vendor    : %s\n", vendor);
  printf("GL Renderer  : %s\n", renderer);
  printf("GL Version (string)  : %s\n", version);
  // printf("GL Version (integer) : %d.%d\n", major, minor);
  printf("GLSL Version : %s\n\n", glslVersion);
}

bool Utils::getChildNode(YAML::Node *childNode, Node node, string key,
                         bool required) {
  *childNode = node[key];
  if (!childNode->IsDefined()) {
    if (required) {
      throw new AssetLoadException(
          AssetLoadException::AssetLoadExceptionReason::AssetDefMissingKey,
          key);
    } else {
      return false;
    }
  }
  return true;
}

//
//  Utils.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "Utils/Utils.h"

using namespace boost;
using namespace ci;

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
    throw std::exception(); // Error getting path
  } else {
    return filesystem::path(pathbuf);
  }

#else
  // TODO: Implement other OS
  throw std::exception();
#endif
}

filesystem::path Utils::getResourcesPath() {
#if defined __APPLE__ && __MACH__
  return getCurrentExecutablePath().parent_path() /
         filesystem::path(OSX_RESOURCE_DIR);
#else
  // TODO: Implement other OS
  throw std::exception();
#endif
}

std::string Utils::strToUpper(std::string inputString) {
  std::string s = std::string(inputString);
  for (auto &c : s)
    c = toupper(c);
  return s;
}

bool Utils::existsIn(std::string sourceString, std::string searchString) {
  return strToUpper(sourceString).find(strToUpper(searchString)) !=
         std::string::npos;
}

bool Utils::isInside(ci::AxisAlignedBox3f bounds, ci::Vec2f point) {
  return (point.x >= bounds.getMin().x && point.x <= bounds.getMax().x &&
          point.y >= bounds.getMin().y && point.y <= bounds.getMax().y);
}

bool Utils::isInside(ci::AxisAlignedBox3f bounds, ci::Vec3f point) {
  return (point.x >= bounds.getMin().x && point.x <= bounds.getMax().x &&
          point.y >= bounds.getMin().y && point.y <= bounds.getMax().y &&
          point.z >= bounds.getMin().z && point.z <= bounds.getMax().z);
}

bool Utils::areOverlapping(ci::AxisAlignedBox3f bounds, ci::Rectf rect) {
  return (bounds.getMin().x < rect.x2 && bounds.getMax().x > rect.x1 &&
          bounds.getMin().y < rect.y2 && bounds.getMax().y > rect.y1);
}

AxisAlignedBox3f Utils::combineBounds(AxisAlignedBox3f first,
                                      AxisAlignedBox3f second) {
  float minX = min(first.getMin().x, first.getMin().x);
  float minY = min(first.getMin().y, first.getMin().y);
  float minZ = min(first.getMin().z, first.getMin().z);

  float maxX = max(first.getMax().x, first.getMax().x);
  float maxY = max(first.getMax().y, first.getMax().y);
  float maxZ = max(first.getMax().z, first.getMax().z);

  return AxisAlignedBox3f(Vec3f(minX, minY, minZ), Vec3f(maxX, maxY, maxZ));
}

void Utils::printOpenGlVersionInfo() {
/*
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
  printf("GLSL Version : %s\n\n", glslVersion);*/
}

bool Utils::getChildNode(YAML::Node *childNode, Node node, string key,
                         bool required) {
  *childNode = node[key];
  if (!childNode->IsDefined()) {
    if (required) {
      throw AssetLoadException(
          AssetLoadException::AssetLoadExceptionReason::AssetDefMissingKey,
          key);
    } else {
      return false;
    }
  }
  return true;
}

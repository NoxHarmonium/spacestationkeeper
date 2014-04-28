//
//  BaseMesh.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#ifndef SpaceStationKeeper_BaseMesh_h
#define SpaceStationKeeper_BaseMesh_h

#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"

using namespace ci;

class BaseMesh {
public:
  virtual void render() = 0;
  virtual AxisAlignedBox3f getBoundingBox() = 0;
};

#endif

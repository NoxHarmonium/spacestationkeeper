//
//  SimpleMesh.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#ifndef SpaceStationKeeper_SimpleMesh_h
#define SpaceStationKeeper_SimpleMesh_h

#include "BaseMesh.h"
#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"
#include <iostream>

using namespace ci;

class SimpleMesh : public BaseMesh {
public:
  void render();
  AxisAlignedBox3f getBoundingBox() { return _bounds; }
  static SimpleMesh *generateQuad(Rectf dimensions, Rectf uv);

private:
  SimpleMesh(TriMesh mesh);
  TriMesh _currentMesh;
  AxisAlignedBox3f _bounds;
};

#endif

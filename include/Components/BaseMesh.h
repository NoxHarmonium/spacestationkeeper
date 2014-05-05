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
/*! The base class for meshes rendered by a RenderComponent. */
class BaseMesh {
public:
  // Constructors/Destructors
  BaseMesh() {};
  virtual ~BaseMesh() {};

  // Methods
  /*! Draws the mesh. */
  virtual void render() = 0;
  /*! Gets the internal mesh representation of the mesh. */
  virtual TriMesh *getInternalMesh() = 0;
  /*! Gets the bounds of the mesh. */
  virtual AxisAlignedBox3f getBoundingBox() = 0;
};

typedef std::shared_ptr<BaseMesh> BaseMeshRef;

#endif

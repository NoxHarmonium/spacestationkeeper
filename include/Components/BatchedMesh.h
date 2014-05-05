//
//  BatchedMesh.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 5/05/2014.
//
//

#include "BaseMesh.h"
#include "cinder/gl/Vbo.h"

#ifndef SpaceStationKeeper_BatchedMesh_h
#define SpaceStationKeeper_BatchedMesh_h

using namespace ci;
using namespace std;

class BatchedMesh : public BaseMesh {
  // Constructors/Destructors
  BatchedMesh();
  ~BatchedMesh();

  // Methods
  /*! Draws the mesh. */
  virtual void render();
  /*! Gets the internal mesh representation of the mesh. */
  virtual TriMesh *getInternalMesh();
  /*! Gets the bounds of the mesh. */
  virtual AxisAlignedBox3f getBoundingBox();
  /*! Adds a mesh to the batch. */
  virtual void addMesh(BaseMeshRef mesh);

private:
  // Methods
  void regenerateVboMesh();
  
  // Fields
  /*! The internal mesh respresentation if the mesh. */
  TriMesh _currentMesh;
  /*! The bounds of the mesh. */
  AxisAlignedBox3f _bounds;
  /*! The VBO representation of the mesh. */
  gl::VboMeshRef _vboMesh;
  /*! The list of meshes that will be batched. */
  vector<BaseMeshRef> _meshes;
};

#endif

//
//  BatchedMesh.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 5/05/2014.
//
//

#include "BaseMesh.h"
#include "cinder/gl/Vbo.h"
#include "Material.h"
#include "Transform.h"
#include "BatchInfo.h"

#ifndef SpaceStationKeeper_BatchedMesh_h
#define SpaceStationKeeper_BatchedMesh_h

using namespace ci;
using namespace std;

class BatchedMesh : public BaseMesh {
public:
  // Constructors/Destructors
  BatchedMesh();
  ~BatchedMesh();

  // Methods
  /*! Draws the mesh. */
  virtual void render();
  /*! Gets the internal mesh representation of the mesh. */
  virtual TriMesh *getInternalMesh();
  /*! Gets the internal mesh representation of the mesh translated according to
   * a transform matrix. */
  virtual TriMesh *getInternalMesh(Matrix44f transformMatrix);
  /*! Gets the bounds of the mesh. */
  virtual AxisAlignedBox3f getBoundingBox();
  /*! Gets the bounds of the mesh translated according to a transform matrix. */
  virtual AxisAlignedBox3f getBoundingBox(Matrix44f transformMatrix);
  /*! Adds a mesh to the batch. */
  virtual void addMesh(BatchInfoRef batchInfo);
  /*! Notifies that the information in a BatchInfo has changed. */
  virtual void invalidate(BatchInfoRef batchInfo);

  // TODO: Ability to move mesh to different material or remove mesh

private:
  // Methods
  void regenerateVboMesh(MaterialRef material);
  /*! Coeleces different materials with the same properties into a single
   * material for batching. */
  MaterialRef getBatchMaterial(MaterialRef material);

  // Fields
  /*! The internal mesh respresentation if the mesh. */
  TriMesh _currentMesh;
  /*! The bounds of the mesh. */
  AxisAlignedBox3f _bounds;
  /*! The VBO representation of the mesh. */
  map<MaterialRef, gl::VboMeshRef> _vboMeshes;
  /*! Stores the current material that the BatchInfo represents. */
  map<BatchInfoRef, MaterialRef> _batchMaterials;
  /*! Stores the current mesh that the BatchInfo represents. */
  map<BatchInfoRef, BaseMeshRef> _batchMeshes;
  /*! The list of meshes that will be batched. */
  map<MaterialRef, set<BatchInfoRef>> _meshes;
  /*! Stores the bounds of each material that can be combined for the primary
   * bounds. */
  map<MaterialRef, AxisAlignedBox3f> _materialBounds;
  /*! Determines whether the batched mesh needs to be regenerated on the next
   * update cycle. */
  map<MaterialRef, bool> _dirty;
};

typedef std::shared_ptr<BatchedMesh> BatchedMeshRef;

#endif

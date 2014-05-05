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
  /*! Adds a mesh to the batch. */
  virtual void addMesh(MaterialRef material, BaseMeshRef mesh,
                       TransformRef transform = TransformRef());
  // TODO: Ability to move mesh to different material or remove mesh

private:
  // Methods
  void regenerateVboMesh(MaterialRef material);

  // Fields
  /*! The internal mesh respresentation if the mesh. */
  TriMesh _currentMesh;
  /*! The bounds of the mesh. */
  AxisAlignedBox3f _bounds;
  /*! The VBO representation of the mesh. */
  map<MaterialRef, gl::VboMeshRef> _vboMeshes;
  /*! The list of meshes that will be batched. */
  map<MaterialRef, vector<TriMesh *>> _meshes;
  /*! Determines whether the batched mesh needs to be regenerated on the next
   * update cycle. */
  map<MaterialRef, bool> _dirty;
};

typedef std::shared_ptr<BatchedMesh> BatchedMeshRef;

#endif

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

namespace BlazeEngine {
namespace Components {

using namespace ci;

class SimpleMesh : public BaseMesh {
public:
  // Constructors/Destructors
  SimpleMesh(TriMesh mesh);
  ~SimpleMesh() {};

  // Methods
  /*! Draws the mesh. */
  virtual void render() override;
  /*! Gets the internal mesh representation of the mesh. */
  virtual TriMesh *getInternalMesh() override;
  /*! Gets the internal mesh representation of the mesh translated according to
   * a transform matrix. */
  virtual TriMesh *getInternalMesh(Matrix44f transformMatrix) override;
  /*! Gets the bounds of the mesh. */
  virtual AxisAlignedBox3f getBoundingBox() override;
  /*! Gets the bounds of the mesh translated according to a transform matrix. */
  virtual AxisAlignedBox3f getBoundingBox(Matrix44f transformMatrix) override;

  // Static Methods
  /*! Generates a simple quad with the specified dimenstions and UV coordinates.
   */
  static std::shared_ptr<BaseMesh> generateQuad(Rectf dimensions, Rectf uv);

private:
  // Fields
  /* The internal mesh respresentation if the mesh. */
  TriMesh _currentMesh;
  /* The bounds of the mesh. */
  AxisAlignedBox3f _bounds;
};

typedef std::shared_ptr<SimpleMesh> SimpleMeshRef;
}
}

#endif

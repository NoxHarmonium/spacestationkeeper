//
//  Transform.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#ifndef SpaceStationKeeper_Transform_h
#define SpaceStationKeeper_Transform_h

#include "pch.h"

using namespace ci;

class Transform {
public:
  // Methods
  /*! Gets a Matrix44 object which represents the transform in local space. */
  Matrix44f getTransformMatrixLocal();
  /*! Gets a Matrix44 object which represents the transform in global space
   * (adjusted for camera). */
  Matrix44f getTransformMatrixWorld();

  // Fields
  Vec3f localPosition = Vec3f(0.0f, 0.0f, 0.0f);
  Quatf localRotation = Quatf::identity();
  Vec3f localScale = Vec3f(1.0f, 1.0f, 1.0f);
  std::shared_ptr<Transform> parent = nullptr;

private:
  // Methods
  void recursiveApplyTransformMatrix(Transform *transform,
                                     Matrix44f *prevMatrix);
};

typedef std::shared_ptr<Transform> TransformRef;

#endif

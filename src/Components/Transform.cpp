//
//  Transform.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 5/05/2014.
//
//

#include "Transform.h"

using namespace ci;

Matrix44f Transform::getTransformMatrix() {
  Matrix44f tMatrix;
  recursiveApplyTransformMatrix(this, &tMatrix);
  return tMatrix;
}

void Transform::recursiveApplyTransformMatrix(Transform *transform,
                                              Matrix44f *tMatrix) {
  if (transform != nullptr) {
    recursiveApplyTransformMatrix(transform->parent.get(), tMatrix);
    tMatrix->translate(transform->localPosition);
    // TODO: Rotation
    // tMatrix->rotate(transform->localRotation.getAxis(),
    //                transform->localRotation.getAngle());
    tMatrix->scale(transform->localScale);
  }
}
//
//  TranformModifier.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/04/2014.
//
//

#include "TransformModifier.h"

using namespace ci;

TransformModifierRef TransformModifier::fromTransform(Transform baseTransform) {
  return TransformModifierRef(new TransformModifier(baseTransform.localPosition,
                                                    baseTransform.localRotation,
                                                    baseTransform.localScale));
}

void TransformModifier::translateBy(Vec3f translation) {
  _translation += translation;
}
void TransformModifier::rotateBy(Quatf rotation) {
  _rotation = rotation * _rotation; // todo: check if this is how to apply delta
                                    // rotation to quaterions
}
void TransformModifier::scaleBy(Vec3f scale) { _scale = _scale * scale; }

Transform *TransformModifier::applyModification(Transform *source) {
  source->localPosition = _translation;
  source->localRotation = _rotation * source->localRotation; // TODO: See above
  source->localScale = _scale;
  return source;
}

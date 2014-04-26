//
//  TransformModifier.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/04/2014.
//
//

#ifndef SpaceStationKeeper_TransformModifier_h
#define SpaceStationKeeper_TransformModifier_h

#include "Transform.h"

using namespace ci;

class TransformModifier {
public:
  void translateBy(Vec3f translation);
  void rotateBy(Quatf rotation);
  void scaleBy(Vec3f scale);

  static std::shared_ptr<TransformModifier>
  fromTransform(Transform baseTransform);

  Transform *applyModification(Transform *source);

private:
  TransformModifier(Vec3f localPosition, Quatf localRotation, Vec3f localScale)
      : _translation(localPosition), _rotation(localRotation),
        _scale(localScale) {};

  Vec3f _translation = Vec3f(0.0f, 0.0f, 0.0f);
  Quatf _rotation = Quatf::identity();
  Vec3f _scale = Vec3f(1.0f, 1.0f, 1.0f);
};

typedef std::shared_ptr<TransformModifier> TransformModifierRef;

#endif

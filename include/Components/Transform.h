//
//  Transform.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#ifndef SpaceStationKeeper_Transform_h
#define SpaceStationKeeper_Transform_h

using namespace ci;

class Transform {
public:
  Vec3f localPosition = Vec3f(0.0f, 0.0f, 0.0f);
  Quatf localRotation = Quatf::identity();
  Vec3f localScale = Vec3f(1.0f, 1.0f, 1.0f);
  std::shared_ptr<Transform> parent = nullptr;
};

typedef std::shared_ptr<Transform> TransformRef;

#endif

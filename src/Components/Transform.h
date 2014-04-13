//
//  Transform.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#ifndef SpaceStationKeeper_Transform_h
#define SpaceStationKeeper_Transform_h

class Transform {
public:
  Vec3f localPosition;
  Quatf localRotation;
  Vec3f localScale;
  Transform *parent = nullptr;
};

#endif

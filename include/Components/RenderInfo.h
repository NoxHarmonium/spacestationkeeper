//
//  RenderInfo.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_Renderer_h
#define SpaceStationKeeper_Renderer_h

#include "Transform.h"
#include "BaseMesh.h"
#include "Material.h"

class RenderInfo {
public:
  RenderInfo() { this->transform = make_shared<Transform>(); }

  bool renderEnabled = true;

  TransformRef transform;
  BaseMeshRef mesh = nullptr;
  MaterialRef material;

  virtual AxisAlignedBox3f getBounds() { return AxisAlignedBox3f(); }
  RenderInfo *clone();
};

#endif

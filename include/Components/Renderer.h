//
//  Renderer.h
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
  bool renderEnabled = true;

  Transform transform;
  BaseMesh *mesh = nullptr;
  MaterialRef material;

  virtual bool canRayCast() = 0;
  virtual AxisAlignedBox3f getBounds() = 0;
};

#endif

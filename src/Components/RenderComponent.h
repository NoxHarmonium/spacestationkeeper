//
//  RenderComponent.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#ifndef SpaceStationKeeper_RenderComponent_h
#define SpaceStationKeeper_RenderComponent_h

#include "GameComponent.h"
#include "Transform.h"
#include "BaseMesh.h"
#include "TextureDef.h"

#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/TriMesh.h"
#include "cinder/gl/GlslProg.h"

class RenderComponent : public GameComponent {
public:
  RenderComponent(ComponentDrivenApp *parent);

  Transform transform;
  TextureDef *texture = nullptr;
  BaseMesh *mesh = nullptr;

  void draw();

private:
  void startDraw();
  void endDraw();
  void applyTransfromRecursive(Transform *t);
};

#endif

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
#include "Material.h"

#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/TriMesh.h"
#include "cinder/gl/GlslProg.h"

class RenderComponent : public GameComponent {
public:
  RenderComponent(ComponentDrivenApp *parent);

  bool renderEnabled = true;

  Transform transform;
  BaseMesh *mesh = nullptr;
  MaterialRef material;
  string classFilter;

  virtual bool canRayCast() { return true; }
  virtual AxisAlignedBox3f getBounds() {
    if (mesh) {
      glPushMatrix();
      applyTransfromRecursive(&this->transform);
      Matrix44f matrix;
      glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
      AxisAlignedBox3f transBound = mesh->getBoundingBox().transformed(matrix);
      glPopMatrix();

      return transBound;
    }
    return AxisAlignedBox3f();
  }
  void draw();

private:
  void startDraw();
  void endDraw();
  void applyTransfromRecursive(Transform *t);
};

#endif

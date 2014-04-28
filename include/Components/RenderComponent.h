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
//#include "EventManager.h"
#include "RenderInfo.h"

class RenderComponent : public GameComponent, public RenderInfo {
public:
  RenderComponent(ComponentDrivenApp *parent) : GameComponent(parent) {};

  virtual bool canRayCast() { return true; }
  virtual AxisAlignedBox3f getBounds() {
    if (mesh) {
      glPushMatrix();
      applyTransfromRecursive(this->transform);
      Matrix44f matrix;
      glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
      AxisAlignedBox3f transBound = mesh->getBoundingBox().transformed(matrix);
      glPopMatrix();

      return transBound;
    }
    return AxisAlignedBox3f();
  }

  void draw();

protected:
  virtual RenderInfo *getRenderInfo() { return this; }

private:
  void startDraw(RenderInfo *renderInfo);
  void endDraw(RenderInfo *renderInfo);
  void applyTransfromRecursive(TransformRef t);
};

#endif

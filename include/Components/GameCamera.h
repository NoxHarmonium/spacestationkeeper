//
//  Camera.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#ifndef __SpaceStationKeeper__Camera__
#define __SpaceStationKeeper__Camera__

#include "pch.h"
#include "GameComponent.h"
#include "cinder/Camera.h"
#include "cinder/gl/gl.h"
#include "Transform.h"

class GameCamera : public GameComponent {
public:
  GameCamera();
  virtual void update();

private:
  ci::CameraOrtho _camera;
};

#endif /* defined(__SpaceStationKeeper__Camera__) */

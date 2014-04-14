//
//  Camera.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#ifndef __SpaceStationKeeper__Camera__
#define __SpaceStationKeeper__Camera__

#include "GameComponent.h"
#include "cinder/Camera.h"
#include "cinder/gl/gl.h"

class GameCamera : public GameComponent {
public:
  GameCamera(ComponentDrivenApp *parent);
  void setup();
  void update();
  void draw();
  void mouseMove(MouseEvent event);
  void mouseDown(MouseEvent event);

private:
  ci::CameraOrtho _camera;
  Vec2f _mousePos;
};

#endif /* defined(__SpaceStationKeeper__Camera__) */

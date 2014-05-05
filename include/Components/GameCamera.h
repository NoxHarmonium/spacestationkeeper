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
#include "Transform.h"

class GameCamera : public GameComponent {
public:
  GameCamera(ComponentDrivenApp *parent);
  void setup();
  void update();
  void draw();
  void mouseMove(MouseEvent event);
  void mouseDown(MouseEvent event);
  void mouseWheel(MouseEvent event);

private:
  ci::CameraOrtho _camera;
  Vec2f _mousePos;

  Vec2f _velocity = Vec2f(0.0f, 0.0f);       // Pixels/Second
  float _edgeSensitivity = 25.0f;            // Pixels
  Vec2f _acceleration = Vec2f(15.0f, 15.0f); // Pixels/Second/Second
  Vec2f _deceleration = Vec2f(0.92f, 0.92f);
  float _maxSpeed = 40.0f; // Pixels/Second
  float _mouseWheelMult = 0.05f;
  Transform _transform;
};

#endif /* defined(__SpaceStationKeeper__Camera__) */

//
//  Camera.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "GameCamera.h"
#include <math.h>

GameCamera::GameCamera(ComponentDrivenApp *parent) : GameComponent(parent) {}

void GameCamera::setup() {}

void GameCamera::update() {
  if (_mousePos.x < _edgeSensitivity) {
    float multiplier = 1.0f - (_mousePos.x / _edgeSensitivity);
    _velocity +=
        Vec2f(-_acceleration.x * multiplier, 0.0f) * _parentApp->getDeltaTime();
  }
  if (_mousePos.x > app::getWindowWidth() - _edgeSensitivity) {
    float multiplier =
        1.0f - ((app::getWindowWidth() - _mousePos.x) / _edgeSensitivity);
    _velocity +=
        Vec2f(_acceleration.x * multiplier, 0.0f) * _parentApp->getDeltaTime();
  }
  if (_mousePos.y < _edgeSensitivity) {
    float multiplier = 1.0f - (_mousePos.y / _edgeSensitivity);
    _velocity +=
        Vec2f(0.0f, -_acceleration.y * multiplier) * _parentApp->getDeltaTime();
  }
  if (_mousePos.y > app::getWindowHeight() - _edgeSensitivity) {
    float multiplier =
        1.0f - ((app::getWindowHeight() - _mousePos.y) / _edgeSensitivity);
    _velocity +=
        Vec2f(0.0f, _acceleration.y * multiplier) * _parentApp->getDeltaTime();
  }

  _velocity.limit(_maxSpeed);

  _transform.localPosition += (Vec3f)_velocity;

  _velocity *= _deceleration;

  float w = getWindowWidth();
  float h = getWindowHeight();
  _camera.setOrtho(0, w, h, 0, -50, 50);

  ci::gl::setMatrices(_camera);
  ci::gl::translate(-_transform.localPosition);

  // Scale around screen center
  Vec3f scaleOffset = Vec3f((float)app::getWindowWidth() / 2.0f,
                            (float)app::getWindowHeight() / 2.0f, 0.0f);
  ci::gl::translate(scaleOffset);
  ci::gl::scale(_transform.localScale);
  ci::gl::translate(-scaleOffset);
}

void GameCamera::draw() {}

void GameCamera::mouseMove(MouseEvent event) {
  float x = event.getX();
  float y = event.getY();

  // Clamp within screen bounds
  x = max(0.0f, x);
  x = min(x, (float)app::getWindowWidth());
  y = max(0.0f, y);
  y = min(y, (float)app::getWindowHeight());

  _mousePos = Vec2f(x, y);
  // cout << "mouseMove: " << _mousePos << endl;
}

void GameCamera::mouseDown(MouseEvent event) {}

void GameCamera::mouseWheel(MouseEvent event) {
  float scale = event.getWheelIncrement() * _mouseWheelMult;
  // Vec2f dir = (Vec2f(event.getX(), event.getY()) -
  //             -_transform.localPosition.xy()).normalized();
  //_velocity += (_acceleration * _parentApp->getDeltaTime()) * dir * 0.5f;
  _transform.localScale += Vec3f(scale, scale, scale);
}

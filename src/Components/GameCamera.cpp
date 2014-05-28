//
//  Camera.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "GameCamera.h"
#include <math.h>
#include "ComponentDrivenApp.h"

GameCamera::GameCamera() : GameComponent() {}

void GameCamera::update(float deltaTime) {

  float w = getWindowWidth();
  float h = getWindowHeight();
  _camera.setOrtho(0, w, h, 0, -50, 50);

  TransformRef transform = gameObject->getRenderer()->transform;

  ci::gl::setMatrices(_camera);
  ci::gl::translate(-transform->localPosition);

  // Scale around screen center
  // TODO: This doesn't work properly with big maps
  Vec3f scaleOffset = Vec3f((float)app::getWindowWidth() / 2.0f,
                            (float)app::getWindowHeight() / 2.0f, 0.0f);
  ci::gl::translate(scaleOffset);
  ci::gl::scale(transform->localScale);
  ci::gl::translate(-scaleOffset);
}

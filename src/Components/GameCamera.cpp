//
//  Camera.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "GameCamera.h"

GameCamera::GameCamera(AppNative *parent) : GameComponent(parent) {}

void GameCamera::setup() {}

void GameCamera::update() {
  _camera.setOrtho(getWindowWidth(), 0, 0, getWindowHeight(), -1, 1);

  ci::gl::setMatrices(_camera);
}

void GameCamera::draw() {}
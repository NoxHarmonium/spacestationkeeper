//
//  Camera.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "GameCamera.h"

GameCamera::GameCamera(AppNative *parent) : GameComponent(parent) {
  cout << "--->Camera construct..." << endl;
}

void GameCamera::setup() { cout << "--->Camera setup..." << endl; }

void GameCamera::update() {
  _camera.setOrtho(0, getWindowWidth(), getWindowHeight(), 0, -1, 1);

  //_camera.setWorldUp(ci::Vec3f(0, 1, 0));
  //_camera.setEyePoint(ci::Vec3f(0, 0, 0));
  //_camera.setCenterOfInterestPoint(ci::Vec3f::zero());
  //_camera.setViewDirection(ci::Vec3f(0, 1, 0));

  ci::gl::setMatrices(_camera);
}

void GameCamera::draw() {}
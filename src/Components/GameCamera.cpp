//
//  Camera.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "GameCamera.h"

GameCamera::GameCamera(AppNative *parent) : GameComponent(parent) {}

void GameCamera::Setup() {

  ci::CameraOrtho cam;

  cam.setOrtho(0, getWindowWidth(), getWindowHeight(), 0, -1, 1);

  cam.setWorldUp(ci::Vec3f(0, 1, 0));
  cam.setEyePoint(ci::Vec3f(0, 0, 0));
  cam.setCenterOfInterestPoint(ci::Vec3f::zero());
  cam.setViewDirection(ci::Vec3f(0, 1, 0));

  _currentCam = cam;
}

void GameCamera::Update() {}

void GameCamera::Draw() {
  // ci::gl::enableDepthRead();
  ci::gl::setMatrices(_currentCam);
}
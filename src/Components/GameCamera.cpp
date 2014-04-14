//
//  Camera.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/03/2014.
//
//

#include "GameCamera.h"

GameCamera::GameCamera(ComponentDrivenApp *parent) : GameComponent(parent) {}

void GameCamera::setup() {}

void GameCamera::update() {
  _camera.setOrtho(0, getWindowWidth(), getWindowHeight(), 0, -50, 50);

  ci::gl::setMatrices(_camera);
}

void GameCamera::draw() {}

void GameCamera::mouseMove(MouseEvent event) {
  _mousePos = Vec2f(event.getX(), event.getY());
  // cout << "mouseMove: " << _mousePos << endl;
}

void GameCamera::mouseDown(MouseEvent event) {}

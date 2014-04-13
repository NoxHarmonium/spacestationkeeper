#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Cairo.h"
#include "GuiManager.h"
#include "ComponentDrivenApp.h"
#include "GameGrid.h"
#include "GameCamera.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cinder::cairo;

class SpaceStationKeeperApp : public ComponentDrivenApp {

public:
  void prepareSettings(Settings *settings);
  void setup();
  void draw();
  void resize();

private:
  GuiManager *_guiManager;
  GameGrid *_gameGrid;
  GameCamera *_camera;
};

void SpaceStationKeeperApp::prepareSettings(Settings *settings) {
  settings->setFrameRate(60);
}

void SpaceStationKeeperApp::resize() {
  // setup(); // reset app
  ComponentDrivenApp::resize();
}

void SpaceStationKeeperApp::setup() {
  // Register all the components that will be sent app events
  _camera = new GameCamera(this);
  _gameGrid = new GameGrid(this);
  _guiManager = new GuiManager(this);

  RegisterComponent(_camera);
  RegisterComponent(_gameGrid);
  // RegisterComponent(_guiManager); Todo: render with quads so depth works

  // Make sure that components get setup
  ComponentDrivenApp::setup();
}

void SpaceStationKeeperApp::draw() {
  // clear out the window with black
  gl::clear(Color(0, 0, 0), true);

  // gl::enableDepthRead();
  // gl::enableDepthWrite();
  gl::enableAlphaBlending();
  // Make sure that the components get drawn
  ComponentDrivenApp::draw();
}

CINDER_APP_NATIVE(SpaceStationKeeperApp, RendererGl)

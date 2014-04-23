#include "SpaceStationKeeperApp.h"
#include "Events.h"
#include "MouseOverTrigger.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cinder::cairo;

void SpaceStationKeeperApp::prepareSettings(Settings *settings) {
  // Utils::printOpenGlVersionInfo();

  settings->setFrameRate(60);
}

void SpaceStationKeeperApp::resize() {
  // setup(); // reset app
  ComponentDrivenApp::resize();
}

void SpaceStationKeeperApp::setup() {
  Utils::printOpenGlVersionInfo();

  // Register all the components that will be sent app events
  _eventManager = new EventManager(this);
  MouseOverTrigger *mouseOverTrigger = new MouseOverTrigger(this);
  _eventManager->RegisterEvent(Events::MouseOver, mouseOverTrigger);
  _camera = new GameCamera(this);
  _gameGrid = new GameGrid(this);
  _guiManager = new GuiManager(this);

  RegisterComponent(_eventManager);
  RegisterComponent(mouseOverTrigger);
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

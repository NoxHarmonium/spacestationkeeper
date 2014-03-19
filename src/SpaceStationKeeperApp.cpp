#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Cairo.h"
#include "GuiManager.h"
#include "ComponentDrivenApp.h"
#include "GameGrid.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cinder::cairo;

class SpaceStationKeeperApp : public ComponentDrivenApp {

public:
  void setup();
  void draw();

private:
  GuiManager *_guiManager;
  GameGrid *_gameGrid;
};

void SpaceStationKeeperApp::setup() {
  // Register all the components that will be sent app events
  _gameGrid = new GameGrid(this);
  _guiManager = new GuiManager(this);

  RegisterComponent(_gameGrid);
  RegisterComponent(_guiManager);

  // Make sure that components get setup
  ComponentDrivenApp::setup();
}

void SpaceStationKeeperApp::draw() {
  // clear out the window with black
  gl::clear(Color(0, 0, 0));

  // Make sure that the components get drawn
  ComponentDrivenApp::draw();
}

CINDER_APP_NATIVE(SpaceStationKeeperApp, RendererGl)

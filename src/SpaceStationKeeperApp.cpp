
#include "SpaceStationKeeperApp.h"
#include "Utils.h"

using namespace ci;
using namespace ci::app;
using namespace std;

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

  _camera = new GameCamera();
  _bindingManager = std::unique_ptr<BindingManager>(new BindingManager());
  //_gameGrid = new GameGrid();
  //_guiManager = new GuiManager();
  //_jobManager = new JobManager();

  registerComponent(_camera);
  // registerComponent(_gameGrid);
  // RegisterComponent(_guiManager); Todo: render with quads so depth works
  // registerComponent(_jobManager);

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

void SpaceStationKeeperApp::keyDown(KeyEvent event) {

  /*if (event.getCode() == KeyEvent::KEY_m) { // TODO: Implement proper control
                                            // system, this is for debugging
    ComponentSet *pSet =
        getState<ComponentSet *>(ToggleSelectionBehaviour::stateKeyName);
    for (GameComponent *tileComp : *pSet) {
      GameTile *tile = (GameTile *)tileComp;
      MiningJob *job = new MiningJob(_gameGrid, tile->getMapPoint(),
                                     _gameGrid->getAssetLoader());
      _jobManager->registerJob(JobRef(job));
    }
    pSet->clear();
  }*/
}

CINDER_APP_NATIVE(SpaceStationKeeperApp, RendererGl)

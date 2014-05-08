
#include "SpaceStationKeeperApp.h"
#include "AssetLoadException.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost;

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

  _fileAssetLoader = make_shared<FileAssetLoader>(Utils::getResourcesPath());
  _bindingManager = std::unique_ptr<BindingManager>(new BindingManager());
  _bindingManager->initialiseBindings();
  scanAssetsAndExecuteScripts();

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

void SpaceStationKeeperApp::scanAssetsAndExecuteScripts() {
  filesystem::path rootPath =
      Utils::getResourcesPath() / filesystem::path("assets");
  for (filesystem::recursive_directory_iterator end, dir(rootPath); dir != end;
       ++dir) {

    filesystem::path p = dir->path();
    if (p.filename() == "assetdef.yaml") {
      string pDir = p.parent_path().string();
      string assetRef =
          getRelativePath(pDir, rootPath); // Get the relative path
      cout << "Loading asset: " << assetRef << endl;
      try {
        AssetDefBaseRef asset = _fileAssetLoader->loadAsset(assetRef);
        cout << "--> Found asset: id: " << asset->getId()
             << " type: " << asset->getAssetType() << endl;
      }
      catch (const AssetLoadException &e) {
        cout << "--> Error loading asset: " << e.what() << endl;
      }
    }
  }
}

string SpaceStationKeeperApp::getRelativePath(
    filesystem::path p, filesystem::path root = filesystem::current_path()) {
  return p.string().substr(root.string().length());
}

CINDER_APP_NATIVE(SpaceStationKeeperApp, RendererGl)
